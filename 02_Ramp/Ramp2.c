#include "stdio.h"

#define RampSampleTime (0.0005f)

typedef enum
{
    RP_BUSY = 0,
    RP_IDLE
} Rp_State_t;

typedef struct
{
    float RemainingTick; // 剩余步数
    float SampleTime;    // 循环所在采样时间
    float SingleStep;    // 步进值
    float PrewTarget;    // 上一次目标值
    float PrewTime;      // Ramp时间
    float Initialval;    // Ramp前的初始值
    float Finalval;
    Rp_State_t State;
} RampMng_t;

void InitRampMng(RampMng_t *pHandle, float value)
{
    pHandle->RemainingTick = 0;
    pHandle->SampleTime = value;
    pHandle->SingleStep = 0;
    pHandle->PrewTarget = 0;
    pHandle->PrewTime = 0;
    pHandle->Initialval = 0;
    pHandle->State = RP_IDLE;
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

unsigned char Ramp2(RampMng_t *pHandle, float *Initval, float wFinalval, float wTime)
{
    if (pHandle->RemainingTick > 0)
    {
        if (pHandle->RemainingTick == 1)
        {
            *Initval = wFinalval;
            pHandle->State = RP_IDLE;
            pHandle->RemainingTick--;
            return 1U;
        }
        else
        {
            *Initval += pHandle->SingleStep;
        }
        pHandle->RemainingTick--;
    }

    if (*Initval == wFinalval)
    {
        /* Nothing */
    }
    else
    {
        if (pHandle->State == RP_IDLE)
        {
            // float RealTime = (wFinalval - *Initval) / wTime;
            // if (RealTime < 0)
            // {
            //     RealTime *= -1.0f;
            // }

            // pHandle->Initialval = *Initval;
            pHandle->RemainingTick = wTime / pHandle->SampleTime;
            pHandle->SingleStep = (wFinalval - *Initval) / pHandle->RemainingTick;

            /* Store Initval */
            // pHandle->PrewTarget = wFinalval;
            // pHandle->PrewTime = wTime;}
            pHandle->State = RP_BUSY;
        }
    }

    return 0U;
}

int main()
{
    RampMng_t Ramp1;
    RampMng_t Ramp_box2;
    InitRampMng(&Ramp1, 0.1f);
    InitRampMng(&Ramp_box2, 0.5f);
    float scope = 0;
    float speedref = 0;
    float speed = 0;

    float speedref2 = 0;
    unsigned char flag = 0;
    for (int i = 0; i < 11; i++)
    {
        // speedref = Ramp(&Ramp1, speedref, 10, 1);

        flag = Ramp2(&Ramp_box2, &speedref2, 15, 5); // printf("%f ", speedref);

        printf("%f ", speedref2);
        if (flag == 1U)
        {
            printf("123\n");
        }
    }
    printf("\n");

    for (int i = 0; i < 11; i++)
    {
        Ramp2(&Ramp_box2, &speedref2, 4, 5);
        printf("%f ", speedref2);
    }
    for (int i = 0; i < 11; i++)
    {
        Ramp2(&Ramp_box2, &speedref2, 33, 5);
        printf("%f ", speedref2);
    }

    return 0;
}
