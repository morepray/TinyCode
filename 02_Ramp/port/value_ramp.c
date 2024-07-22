/**
 * @file value_ramp.c
 * @author zhang song (morepray@163.com)
 * @brief
 * @version 0.1
 * @date 2024-05-12
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "value_ramp.h"

void InitRampMng(RampMng_t *pHandle, float wSampleTime)
{
    pHandle->State = RP_IDLE;
    pHandle->RemainingTick = 0;
    pHandle->SampleTime = wSampleTime;
    pHandle->SingleStep = 0.0f;
    pHandle->Reference = 0.0f;
}

/**
 * @brief 斜坡函数，完成返回1
 *
 * @param pHandle
 * @param wElement
 * @param wFinalval
 * @param wTime
 * @return 完成返回1, 未完成返回0
 */
uint8_t RampTask(RampMng_t *pHandle, float *wElement, float wFinalval, float wTime)
{
    if (pHandle->RemainingTick > 0)
    {
        /* 完成最后一步的给定 */
        if (pHandle->RemainingTick == 1)
        {
            *wElement = wFinalval;
            pHandle->State = RP_IDLE;
            pHandle->RemainingTick--;
            return 1U;
        }
        else
        {
            *wElement += pHandle->SingleStep;
        }
        pHandle->RemainingTick--;
    }

    /* 当终值与存储的初值相同时 */
    if (*wElement == wFinalval)
    {
        /* Nothing */
    }
    else
    {
        /* 此时如果存在任务，即使终值变化，也不分配任务 */
        if (pHandle->State == RP_IDLE)
        {
            pHandle->RemainingTick = (uint32_t)(wTime / pHandle->SampleTime);
            pHandle->SingleStep = (wFinalval - *wElement) / ((float)(pHandle->RemainingTick));
            pHandle->State = RP_BUSY;
        }
    }

    return 0U;
}
