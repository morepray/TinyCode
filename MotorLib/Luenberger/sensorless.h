#ifndef __SENSORLESS_H
#define __SENSORLESS_H

#include "stdint.h"

#define STO_2PI (6.283185307179586f)

#define STO_LS (0.00011f)
#define STO_RS (0.06f)
#define STO_NUM_OF_POLE (5.0f)
#define STO_Tpwm (0.0000625f)

#define L_e1 (1.0f - STO_RS * STO_Tpwm / STO_LS)
#define L_e2 (1.0f)
#define L_e1obs (L_e1 * STO_Tpwm)
#define L_e2obs (L_e2 * STO_Tpwm)

#define G1Default -((L_e1obs + L_e2obs - 2.0f) / STO_Tpwm + STO_RS / STO_LS)
#define G2Default -(STO_LS * (1.0f - L_e1obs - L_e2obs + L_e2obs * L_e2obs) / STO_Tpwm / STO_Tpwm)

#define PLL_KpDefault (30.0f * 532.0f * 50.0f / 16000.0f)
#define PLL_KiDefault (30.0f * 1506742.0f * 50.0f / 16000.0f / 16000.0f)

typedef struct
{
    float hMecSpeed;

    float hElAngle;
    float hElAngleDpp;
    float hElSpeed;
    float hElSpeedDpp;
    float hElAngleConpen;

    char hDirection;
    float EltoMecCoef;
} Observer_t;

typedef struct
{
    float hKpGain;
    float hKiGain;
    float wIntegralTerm;
    float wUpperIntegralLimit;
    float wLowerIntegralLimit;
    float hUpperOutputLimit;
    float hLowerOutputLimit;
} STO_PID_Handle_t;

typedef struct
{
    float Buffer[64];
    uint8_t BufferSizeUnit;
    uint8_t Buffer_Index;
    float BufferOldestEl;
    float BufferSum;
    uint8_t BufferFillSize;
    float wAverage;
    float wAvrQuadraticError;
} STO_Store_Handle_t;

typedef enum
{
    STO_BUSY = 0,
    STO_IDLE,
} Force_enum_t;
typedef struct
{
    float VIR_hElAngle;
    float VIR_hElAngleDpp;
    float VIR_hElSpeed;
    float STO_hElAngle;
    Force_enum_t State;
} Force_t;

float STO_Get_hElAngle(void);
float STO_Get_hElSpeed(void);
float STO_Get_hMecSpeed(void);
void StateObserverInit(void);
void StateObserverTask(float wElSpeed, float wIalpha, float wIbeta, float wValpha, float wVbeta);

uint8_t STO_ForceAngleRamp(float *VIR_Angle, float *VIR_Speed, float *VIR_AngleDpp, float *Iqref, float IqrefTarget);
#endif
