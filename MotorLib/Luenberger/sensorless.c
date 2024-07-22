#include "sensorless.h"

#include "STO.h"
// #include "mc_math.h"
#include "arm_math.h"

/**
 * @brief 移植
 * 1. StateObserverTask(), 放到PWM中断
 * 2. StateObserverInit(), 在初始化中放，停止电机时调用
 * 3. STO_ForceAngleRamp, 放在角度切换状态中
 * float STO_Get_hElAngle(void);放到PWM中断
 * float STO_Get_hElSpeed(void);放到PWM中断
 * float STO_Get_hMecSpeed(void);放到PWM中断
 */

Observer_t Observer_M1;
STO_Store_Handle_t STO_PLL_M1 = {
    .BufferSizeUnit = 64,
    .BufferFillSize = 0,
    .Buffer_Index = 0,
    .BufferOldestEl = 0.0f,
    .BufferSum = 0.0f,
    .wAverage = 0.0f,
    .wAvrQuadraticError = 0.0f,
};
STO_PID_Handle_t PIDPLLHandle_M1 = {
    // .hKpGain = PLL_KpDefault,
    // .hKiGain = PLL_KiDefault,
    .hKpGain = 40.0f,
    .hKiGain = 0.15f,
    .wUpperIntegralLimit = (float)(2147483647),
    .wLowerIntegralLimit = (float)(-2147483647),
    .hUpperOutputLimit = 3000.0f / 60.0f * STO_NUM_OF_POLE * STO_2PI,
    .hLowerOutputLimit = -3000.0f / 60.0f * STO_NUM_OF_POLE * STO_2PI,
    .wIntegralTerm = 0,
};

Force_t Force_M1 = {
    .VIR_hElAngle = 0.0f,
    .VIR_hElAngleDpp = 0.0f,
    .VIR_hElSpeed = 0.0f,
    .STO_hElAngle = 0.0f,
    .State = STO_IDLE,
};

void ObserverInit(void)
{
    Observer_M1.hMecSpeed = 0.0f;
    Observer_M1.hElAngle = 0.0f;
    Observer_M1.hElAngleConpen = 0.0f;
    Observer_M1.hElAngleDpp = 0.0f;
    Observer_M1.hElSpeed = 0.0f;
    Observer_M1.hElSpeedDpp = 0.0f;
    Observer_M1.hDirection = 1;
    Observer_M1.EltoMecCoef = 60.0f / STO_2PI / STO_NUM_OF_POLE;
}
float STO_Get_hElAngle(void)
{
    return (Observer_M1.hElAngle);
}
float STO_Get_hElSpeed(void)
{
    return (Observer_M1.hElSpeed);
}
float STO_Get_hMecSpeed(void)
{
    return (Observer_M1.hMecSpeed);
}
void STO_SetPIDwIntegralTerm(float num)
{
    PIDPLLHandle_M1.wIntegralTerm = num;
}
float STO_PI_Controller(STO_PID_Handle_t *pHandle, float wProcessVarError)
{
    float wProportional_Term, wIntegral_Term, wOutput_32, wIntegral_sum_temp;
    float wDischarge = 0;
    float hUpperOutputLimit = pHandle->hUpperOutputLimit;
    float hLowerOutputLimit = pHandle->hLowerOutputLimit;

    /* Proportional term computation*/
    wProportional_Term = pHandle->hKpGain * wProcessVarError;

    /* Integral term computation */
    if (pHandle->hKiGain == 0)
    {
        pHandle->wIntegralTerm = 0;
    }
    else
    {
        wIntegral_Term = pHandle->hKiGain * wProcessVarError;
        wIntegral_sum_temp = pHandle->wIntegralTerm + wIntegral_Term;

        if (wIntegral_sum_temp < 0)
        {
            if (pHandle->wIntegralTerm > 0)
            {
                if (wIntegral_Term > 0)
                {
                    wIntegral_sum_temp = pHandle->wUpperIntegralLimit;
                }
            }
        }
        else
        {
            if (pHandle->wIntegralTerm < 0)
            {
                if (wIntegral_Term < 0)
                {
                    wIntegral_sum_temp = pHandle->wLowerIntegralLimit;
                }
            }
        }

        if (wIntegral_sum_temp > pHandle->wUpperIntegralLimit)
        {
            pHandle->wIntegralTerm = pHandle->wUpperIntegralLimit;
        }
        else if (wIntegral_sum_temp < pHandle->wLowerIntegralLimit)
        {
            pHandle->wIntegralTerm = pHandle->wLowerIntegralLimit;
        }
        else
        {
            pHandle->wIntegralTerm = wIntegral_sum_temp;
        }
    }

    wOutput_32 = wProportional_Term + pHandle->wIntegralTerm;

    if (wOutput_32 > hUpperOutputLimit)
    {
        wDischarge = hUpperOutputLimit - wOutput_32;
        wOutput_32 = hUpperOutputLimit;
    }
    else if (wOutput_32 < hLowerOutputLimit)
    {
        wDischarge = hLowerOutputLimit - wOutput_32;
        wOutput_32 = hLowerOutputLimit;
    }
    else
    { /* Nothing to do here */
    }

    pHandle->wIntegralTerm += wDischarge;

    return wOutput_32;
}

void STO_InitSpeedBuffer(STO_Store_Handle_t *pHandle)
{
    for (uint8_t i = 0; i < pHandle->BufferSizeUnit; i++)
    {
        pHandle->Buffer[i] = 0.0f;
    }
    pHandle->Buffer_Index = 0;
    pHandle->BufferFillSize = 0;
    pHandle->BufferSum = 0.0f;
    pHandle->BufferOldestEl = 0.0f;
    pHandle->wAverage = 0.0f;
    pHandle->wAvrQuadraticError = 0.0f;
}

float STO_Store_Element(STO_Store_Handle_t *pHandle, float hElement)
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
 * @brief 锁相环
 *
 */
void PLL_Calcu(void)
{
    float wVarError;
    float wElSpeed;
    float wAux_Ealpha = STO_Y.Ealpha_hat;
    float wAux_Ebeta = STO_Y.Ebeta_hat;

    /* 正反转 */
    wAux_Ealpha *= (float)Observer_M1.hDirection;
    wAux_Ebeta *= (float)Observer_M1.hDirection;

    wVarError = -wAux_Ealpha * arm_cos_f32(Observer_M1.hElAngle) - wAux_Ebeta * arm_sin_f32(Observer_M1.hElAngle);
    wElSpeed = STO_PI_Controller(&PIDPLLHandle_M1, wVarError);
    Observer_M1.hElSpeed = STO_Store_Element(&STO_PLL_M1, wElSpeed);
    Observer_M1.hMecSpeed = Observer_M1.hElSpeed * Observer_M1.EltoMecCoef;
    Observer_M1.hElAngle += Observer_M1.hElSpeed / 16000.0f;
    if (Observer_M1.hElAngle > STO_2PI)
    {
        Observer_M1.hElAngle -= STO_2PI;
    }
    else if (Observer_M1.hElAngle < 0.0f)
    {
        Observer_M1.hElAngle += STO_2PI;
    }
}

/**
 * @brief 龙伯格初始化
 *
 */
void StateObserverInit(void)
{
    ObserverInit();
    STO_initialize();
    STO_InitSpeedBuffer(&STO_PLL_M1);
    STO_SetPIDwIntegralTerm(0.0f);
    STO_U.G1 = G1Default;
    STO_U.G2 = G2Default;
    STO_U.Ls = STO_LS;
    STO_U.Rs = STO_RS;
    STO_U.Ts = STO_Tpwm;
}

void StateObserverTask(float wElSpeed, float wIalpha, float wIbeta, float wValpha, float wVbeta)
{
    /* 虚拟角度积分 */
    if (Force_M1.State == STO_BUSY)
    {
        Force_M1.STO_hElAngle += Observer_M1.hElSpeed / 16000.0f;
        Force_M1.VIR_hElAngle += Force_M1.VIR_hElAngleDpp;
    }

    /* 龙伯格观测代码 */
    STO_U.ElSpeed = wElSpeed;
    STO_U.Ialpha = wIalpha;
    STO_U.Ibeta = wIbeta;
    STO_U.Valpha = wValpha;
    STO_U.Vbeta = wVbeta;
    STO_step();

    /* PLL代码 */
    PLL_Calcu();
}

/**
 * @brief 强迫虚拟角度斜坡到闭环角度
 * 首先需要知道当前编码器的角度，赋值给虚拟编码器，然后与观测器角度做比较
 * 将角度差值作为反馈，加给电角速度通过P控制器进行调节
 *
 * @param VIR_Angle 虚拟编码器的电角度指针
 * @param VIR_Speed 虚拟编码器的电速度指针
 * @param VIR_AngleDpp 虚拟编码器的角度累加值指针
 * @param Iqref q轴给定指针
 * @param IqrefTarget 速度PI的输出
 * @return 完成时返回1
 */
uint8_t STO_ForceAngleRamp(float *VIR_Angle, float *VIR_Speed, float *VIR_AngleDpp, float *Iqref, float IqrefTarget)
{
    float wError;
    float OutputIqref;
    if (Force_M1.State == STO_IDLE)
    {
        Force_M1.VIR_hElAngle = *VIR_Angle;
        Force_M1.VIR_hElAngleDpp = *VIR_Speed / 16000.0f;
        Force_M1.STO_hElAngle = Observer_M1.hElAngle;
        Force_M1.State = STO_BUSY;
    }
    else
    {
        wError = (Force_M1.STO_hElAngle - Force_M1.VIR_hElAngle) * 1.5f;
        *VIR_Speed += wError;
        Force_M1.VIR_hElAngleDpp = *VIR_Speed / 16000.0f;
        *VIR_AngleDpp = *VIR_Speed / 16000.0f;

        if ((Force_M1.STO_hElAngle - Force_M1.VIR_hElAngle) < 0.01f && (Force_M1.STO_hElAngle - Force_M1.VIR_hElAngle) > -0.01f)
        {
            Force_M1.State = STO_IDLE;
            return 1;
        }
        OutputIqref = (IqrefTarget - *Iqref) * 0.003f;
        *Iqref += OutputIqref;
    }
    return 0;
}
