#include "stdio.h"
#include <stdlib.h>
#include <time.h>
#include "math.h"

typedef unsigned char uint8_t;
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
} Store_Handle_t;

Store_Handle_t STO_PLL_M1 = {
    .BufferSizeUnit = 64,
    .Buffer_Index = 0.0f,
    .BufferOldestEl = 0.0f,
    .BufferSum = 0.0f,
    .BufferFillSize = 0,
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

uint8_t CalcAvrgElement(Store_Handle_t *pHandle)
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

    if (wAvrQuadraticError < wAvrSquareElement * 0.1f)
    {
        return 1U;
    }
    else
    {
        return 0U;
    }
}
int main()
{
    srand((unsigned)time(NULL));
    int Randnum;
    float Avrf = 0.0f;
    InitStoreBuffer(&STO_PLL_M1);
    for (int i = 0; i < 64; i++)
    {
        Randnum = 800 + rand() % 50;
        Store_Element(&STO_PLL_M1, (float)Randnum);
        printf("%d ", Randnum);
    }
    CalcAvrgElement(&STO_PLL_M1);
    printf("\n方差\t= %f\n", STO_PLL_M1.wAvrQuadraticError);
    printf("标准差\t= %f\n", sqrt(STO_PLL_M1.wAvrQuadraticError));
    printf("平均值\t= %f\n", STO_PLL_M1.wAverage);
    return 0;
}