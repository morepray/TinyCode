/*
 * File: STO.c
 *
 * Code generated for Simulink model 'STO'.
 *
 * Model version                  : 1.399
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Thu Mar  7 12:33:29 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "STO.h"
#include "STO_private.h"

/* Block states (default storage) */
DW_STO_T STO_DW;

/* External inputs (root inport signals with default storage) */
ExtU_STO_T STO_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_STO_T STO_Y;

/* Real-time model */
RT_MODEL_STO_T STO_M_;
RT_MODEL_STO_T *const STO_M = &STO_M_;

/* Model step function */
void STO_step(void)
{
  real32_T Ealpha_hat_tmp;
  real32_T Delay13_DSTATE_tmp;
  real32_T Delay13_DSTATE_tmp_0;

  /* Product: '<S1>/Product2' incorporates:
   *  Inport: '<Root>/G2'
   *  Inport: '<Root>/Ts'
   *  Product: '<S1>/Product3'
   */
  Ealpha_hat_tmp = STO_U.Ts * STO_U.G2;

  /* Sum: '<S1>/Add15' incorporates:
   *  Delay: '<S1>/Delay13'
   *  Delay: '<S1>/Delay16'
   *  Delay: '<S1>/Delay17'
   *  Gain: '<S1>/Gain'
   *  Inport: '<Root>/ElSpeed'
   *  Inport: '<Root>/Ialpha'
   *  Inport: '<Root>/Ts'
   *  Product: '<S1>/Product2'
   *  Product: '<S1>/Product20'
   *  Product: '<S1>/Product21'
   *  Product: '<S1>/Product22'
   *  Sum: '<S1>/Add16'
   */
  STO_Y.Ealpha_hat = (-STO_U.Ts * STO_U.ElSpeed * STO_Y.Ebeta_hat +
                      STO_Y.Ealpha_hat) + Ealpha_hat_tmp * (STO_U.Ialpha -
    STO_DW.Delay13_DSTATE);

  /* Sum: '<S1>/Add14' incorporates:
   *  Delay: '<S1>/Delay12'
   *  Delay: '<S1>/Delay14'
   *  Delay: '<S1>/Delay15'
   *  Delay: '<S1>/Delay16'
   *  Inport: '<Root>/ElSpeed'
   *  Inport: '<Root>/Ibeta'
   *  Inport: '<Root>/Ts'
   *  Product: '<S1>/Product23'
   *  Product: '<S1>/Product24'
   *  Product: '<S1>/Product25'
   *  Sum: '<S1>/Add17'
   */
  STO_Y.Ebeta_hat = (STO_U.Ts * STO_U.ElSpeed * STO_DW.Delay14_DSTATE +
                     STO_Y.Ebeta_hat) + Ealpha_hat_tmp * (STO_U.Ibeta -
    STO_DW.Delay12_DSTATE);

  /* Product: '<S1>/Divide4' incorporates:
   *  Inport: '<Root>/Ls'
   *  Inport: '<Root>/Ts'
   *  Product: '<S1>/Divide2'
   *  Product: '<S1>/Divide3'
   */
  Ealpha_hat_tmp = STO_U.Ts / STO_U.Ls;

  /* Product: '<S1>/Product' incorporates:
   *  Inport: '<Root>/G1'
   *  Inport: '<Root>/Ts'
   *  Product: '<S1>/Product4'
   *  Product: '<S1>/Product5'
   */
  Delay13_DSTATE_tmp = STO_U.Ts * STO_U.G1;

  /* Sum: '<S1>/Add' incorporates:
   *  Constant: '<S1>/Constant'
   *  Inport: '<Root>/Ls'
   *  Inport: '<Root>/Rs'
   *  Inport: '<Root>/Ts'
   *  Product: '<S1>/Divide'
   *  Product: '<S1>/Product'
   *  Product: '<S1>/Product7'
   *  Sum: '<S1>/Add1'
   *  Sum: '<S1>/Add2'
   */
  Delay13_DSTATE_tmp_0 = (1.0F - STO_U.Ts * STO_U.Rs / STO_U.Ls) -
    Delay13_DSTATE_tmp;

  /* Sum: '<S1>/Add12' incorporates:
   *  Delay: '<S1>/Delay13'
   *  Delay: '<S1>/Delay8'
   *  Delay: '<S1>/Delay9'
   *  Gain: '<S1>/Gain1'
   *  Inport: '<Root>/Ialpha'
   *  Inport: '<Root>/Valpha'
   *  Product: '<S1>/Divide4'
   *  Product: '<S1>/Product12'
   *  Product: '<S1>/Product13'
   *  Product: '<S1>/Product14'
   *  Product: '<S1>/Product15'
   *  Sum: '<S1>/Add'
   */
  STO_DW.Delay13_DSTATE = ((Delay13_DSTATE_tmp_0 * STO_DW.Delay8_DSTATE +
    -Ealpha_hat_tmp * STO_DW.Delay9_DSTATE) + Ealpha_hat_tmp * STO_U.Valpha) +
    Delay13_DSTATE_tmp * STO_U.Ialpha;

  /* Sum: '<S1>/Add13' incorporates:
   *  Delay: '<S1>/Delay10'
   *  Delay: '<S1>/Delay11'
   *  Delay: '<S1>/Delay12'
   *  Gain: '<S1>/Gain2'
   *  Inport: '<Root>/Ibeta'
   *  Inport: '<Root>/Ls'
   *  Inport: '<Root>/Ts'
   *  Inport: '<Root>/Vbeta'
   *  Product: '<S1>/Divide5'
   *  Product: '<S1>/Product16'
   *  Product: '<S1>/Product17'
   *  Product: '<S1>/Product18'
   *  Product: '<S1>/Product19'
   */
  STO_DW.Delay12_DSTATE = ((Delay13_DSTATE_tmp_0 * STO_DW.Delay10_DSTATE +
    -(STO_U.Ts / STO_U.Ls) * STO_DW.Delay11_DSTATE) + Ealpha_hat_tmp *
    STO_U.Vbeta) + Delay13_DSTATE_tmp * STO_U.Ibeta;

  /* Update for Delay: '<S1>/Delay14' incorporates:
   *  Delay: '<S1>/Delay17'
   */
  STO_DW.Delay14_DSTATE = STO_Y.Ealpha_hat;

  /* Update for Delay: '<S1>/Delay8' incorporates:
   *  Delay: '<S1>/Delay13'
   */
  STO_DW.Delay8_DSTATE = STO_DW.Delay13_DSTATE;

  /* Update for Delay: '<S1>/Delay9' incorporates:
   *  Delay: '<S1>/Delay17'
   */
  STO_DW.Delay9_DSTATE = STO_Y.Ealpha_hat;

  /* Update for Delay: '<S1>/Delay10' incorporates:
   *  Delay: '<S1>/Delay12'
   */
  STO_DW.Delay10_DSTATE = STO_DW.Delay12_DSTATE;

  /* Update for Delay: '<S1>/Delay11' incorporates:
   *  Delay: '<S1>/Delay16'
   */
  STO_DW.Delay11_DSTATE = STO_Y.Ebeta_hat;
}

/* Model initialize function */
void STO_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(STO_M, (NULL));

  /* states (dwork) */
  (void) memset((void *)&STO_DW, 0,
                sizeof(DW_STO_T));

  /* external inputs */
  (void)memset(&STO_U, 0, sizeof(ExtU_STO_T));

  /* external outputs */
  (void) memset((void *)&STO_Y, 0,
                sizeof(ExtY_STO_T));
}

/* Model terminate function */
void STO_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
