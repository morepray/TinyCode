#include "stdio.h"

#define RampSampleTime (0.0005f)

typedef struct
{
    float RemainingTick; // 剩余步数
    float SampleTime;    // 循环所在采样时间
    float SingleStep;    // 步进值
    float PrewTarget;    // 上一次目标值
    float PrewTime;      // Ramp时间
    float Initialval;    // Ramp前的初始值
} RampMng_t;

void InitRampMng(RampMng_t *pHandle, float value)
{
    pHandle->RemainingTick = 0;
    pHandle->SampleTime = value;
    pHandle->SingleStep = 0;
    pHandle->PrewTarget = 0;
    pHandle->PrewTime = 0;
    pHandle->Initialval = 0;
}

float Ramp(RampMng_t *pHandle, float Initval, float wFinalval, float wTime)
{
    if (pHandle->PrewTarget == wFinalval)
    {
        /* Nothing */
    }
    else
    {
        pHandle->Initialval = Initval;
        pHandle->RemainingTick = wTime / pHandle->SampleTime;
        pHandle->SingleStep = (wFinalval - pHandle->Initialval) / pHandle->RemainingTick;

        /* Store Initval */
        pHandle->PrewTarget = wFinalval;
        pHandle->PrewTime = wTime;
    }

    if (pHandle->RemainingTick > 0)
    {
        if (pHandle->RemainingTick == 1)
        {
            pHandle->Initialval = wFinalval;
        }
        else
            pHandle->Initialval += pHandle->SingleStep;
        pHandle->RemainingTick--;
    }

    return pHandle->Initialval;
}

int main()
{
    RampMng_t Ramp1;
    InitRampMng(&Ramp1, 0.1f);
    float scope = 0;
    float speedref = 100;
    float speed = 0;
    for (int i = 0; i < 21; i++)
    {
        speedref = Ramp(&Ramp1, speedref, 10, 0);
        printf("%f ", speedref);
    }
    for (int i = 0; i < 22; i++)
    {
        speedref = Ramp(&Ramp1, speedref, 30, 1);
        printf("%f ", speedref);
    }

    return 0;
}
