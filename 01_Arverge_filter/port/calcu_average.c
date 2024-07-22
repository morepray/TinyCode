#include "calcu_average.h"

Store_Handle_t Store_Element_M1 = {
    .BufferSizeUnit = 64,
    .BufferFillSize = 0,
    .Buffer_Index = 0.0f,
    .BufferOldestEl = 0.0f,
    .BufferSum = 0.0f,
    .wAverage = 0.0f,
    .wAvrQuadraticError = 0.0f,
};

/**
 * @brief 初始化结构体和数组
 *
 * @param pHandle
 */
void InitStoreBuffer(Store_Handle_t *pHandle)
{
    for (uint8_t i = 0; i < pHandle->BufferSizeUnit; i++)
    {
        pHandle->Buffer[i] = 0.0f;
    }
    pHandle->BufferSum = 0;
    pHandle->Buffer_Index = 0;
    pHandle->BufferOldestEl = 0;
    pHandle->BufferFillSize = 0;
    pHandle->wAverage = 0.0f;
    pHandle->wAvrQuadraticError = 0.0f;
}

/**
 * @brief 平均滤波
 *
 * @param pHandle
 * @param hElement
 * @return float
 */
float Store_Element(Store_Handle_t *pHandle, float hElement)
{
    uint8_t bBuffer_index = pHandle->Buffer_Index;
    float wSum = pHandle->BufferSum;
    float wReturn;
    if (pHandle->BufferFillSize < pHandle->BufferSizeUnit)
    {
        pHandle->BufferFillSize++;
    }

    bBuffer_index++;
    if (bBuffer_index == pHandle->BufferSizeUnit)
    {
        bBuffer_index = 0u;
    }

    pHandle->BufferOldestEl = pHandle->Buffer[bBuffer_index];
    pHandle->Buffer[bBuffer_index] = hElement;
    pHandle->Buffer_Index = bBuffer_index;

    wSum = pHandle->BufferSum + pHandle->Buffer[bBuffer_index] - pHandle->BufferOldestEl;

    if (pHandle->BufferFillSize == pHandle->BufferSizeUnit)
    {
        wReturn = wSum / pHandle->BufferSizeUnit;
    }
    else
    {
        wReturn = wSum / pHandle->BufferFillSize;
    }

    pHandle->BufferSum = wSum;

    return wReturn;
}

/**
 * @brief 计算平均与方差，判断方差是否在平均值平方的Coef倍之内
 *
 * @param pHandle
 * @param Coef
 * @return uint8_t
 */
uint8_t CalcAvrgElement(Store_Handle_t *pHandle, float Coef)
{
    float wArvElement = 0.0f;
    float wError, wAvrQuadraticError, wAvrSquareElement;

    wArvElement = pHandle->BufferSum / pHandle->BufferSizeUnit;

    for (uint8_t i = 0; i < pHandle->BufferSizeUnit; i++)
    {
        wError = pHandle->Buffer[i] - wArvElement;
        wError = (wError * wError);
        wAvrQuadraticError += wError;
    }
    wAvrQuadraticError = wAvrQuadraticError / pHandle->BufferSizeUnit;
    wAvrSquareElement = wArvElement * wArvElement;

    pHandle->wAverage = wArvElement;
    pHandle->wAvrQuadraticError = wAvrQuadraticError;

    if (wAvrQuadraticError < wAvrSquareElement * Coef)
    {
        return 1U;
    }
    else
    {
        return 0U;
    }
}