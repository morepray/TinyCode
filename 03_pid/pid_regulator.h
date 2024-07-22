#ifndef __PIDREGULATOR_H
#define __PIDREGULATOR_H

/**
 * A = Vdc/(2^16)
 * B = R_shunt * Aop * 2^16 / 3.3
 * AB = Vdc * R_shunt * Aop / 3.3
 * Kp = Ls * Wc / (AB)
 * Ki = Rs * Wc * T/ (AB)
 */
// #define PID_TORQUE_KP_DEFAULT (float)(LS * WC / (VBus * Rshunt * Aop / V33))
// #define PID_TORQUE_KI_DEFAULT (float)(RS * WC * Tpwm / (VBus * Rshunt * Aop / V33))
// #define PID_TORQUE_KD_DEFAULT (float)(0.0f)
// #define PID_FLUX_KP_DEFAULT (float)(LS * WC / (VBus * Rshunt * Aop / V33))
// #define PID_FLUX_KI_DEFAULT (float)(RS * WC * Tpwm / (VBus * Rshunt * Aop / V33))
// #define PID_FLUX_KD_DEFAULT (float)(0.0f)

typedef struct PID_Handle
{
    float hKpGain;
    float hKiGain;
    float wIntegralTerm;
    float wUpperIntegralLimit;
    float wLowerIntegralLimit;
    float hUpperOutputLimit;
    float hLowerOutputLimit;
} PID_Handle_t;

float PI_Controller(PID_Handle_t *pHandle, float wProcessVarError);

#endif
