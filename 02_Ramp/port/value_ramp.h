#ifndef __VALUE_RAMP_H
#define __VALUE_RAMP_H

#include "stdint.h"

#define RampSampleTime (0.0005f)

typedef enum
{
    RP_BUSY = 0,
    RP_IDLE
} Rp_State_t;

typedef struct
{
    Rp_State_t State;
    float SampleTime;       // 循环所在采样时间
    uint32_t RemainingTick; // 剩余步数
    float SingleStep;       // 步进值
    float Reference;
} RampMng_t;

void InitRampMng(RampMng_t *pHandle, float value);
uint8_t RampTask(RampMng_t *pHandle, float *wElement, float wFinalval, float wTime);

#endif
