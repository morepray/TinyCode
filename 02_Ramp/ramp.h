#ifndef __RAMP_H
#define __RAMP_H

#include "stdint.h"

#define RampSampleTime (0.0005f)

typedef enum
{
    RP_BUSY = 0,
    RP_IDLE
} Rp_State_t;

typedef struct
{
    uint32_t RemainingTick; // 剩余步数
    float SampleTime;       // 循环所在采样时间
    float SingleStep;       // 步进值
    Rp_State_t State;
    float Reference;
} RampMng_t;

extern RampMng_t RampIq;
extern RampMng_t RampSpeed;

void InitRampMng(RampMng_t *pHandle, float value);
uint8_t RampTask(RampMng_t *pHandle, float *Initval, float wFinalval, float wTime);

#endif
