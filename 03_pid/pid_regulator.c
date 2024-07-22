#include "pid_regulator.h"

float PI_Controller(PID_Handle_t *pHandle, float wProcessVarError)
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
