#ifndef __CALCU_AVERAGE_H
#define __CALCU_AVERAGE_H

#include "stdint.h"

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

extern Store_Handle_t Store_Element_M1;

void InitStoreBuffer(Store_Handle_t *pHandle);
float Store_Element(Store_Handle_t *pHandle, float hElement);
uint8_t CalcAvrgElement(Store_Handle_t *pHandle, float Coef);

#endif
