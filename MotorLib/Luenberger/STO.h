/*
 * File: STO.h
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

#ifndef RTW_HEADER_STO_h_
#define RTW_HEADER_STO_h_
#include <string.h>
#include <stddef.h>
#ifndef STO_COMMON_INCLUDES_
# define STO_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* STO_COMMON_INCLUDES_ */

#include "STO_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real32_T Delay13_DSTATE;             /* '<S1>/Delay13' */
  real32_T Delay14_DSTATE;             /* '<S1>/Delay14' */
  real32_T Delay12_DSTATE;             /* '<S1>/Delay12' */
  real32_T Delay8_DSTATE;              /* '<S1>/Delay8' */
  real32_T Delay9_DSTATE;              /* '<S1>/Delay9' */
  real32_T Delay10_DSTATE;             /* '<S1>/Delay10' */
  real32_T Delay11_DSTATE;             /* '<S1>/Delay11' */
} DW_STO_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real32_T Valpha;                     /* '<Root>/Valpha' */
  real32_T Vbeta;                      /* '<Root>/Vbeta' */
  real32_T ElSpeed;                    /* '<Root>/ElSpeed' */
  real32_T Ialpha;                     /* '<Root>/Ialpha' */
  real32_T Ibeta;                      /* '<Root>/Ibeta' */
  real32_T G1;                         /* '<Root>/G1' */
  real32_T G2;                         /* '<Root>/G2' */
  real32_T Rs;                         /* '<Root>/Rs' */
  real32_T Ls;                         /* '<Root>/Ls' */
  real32_T Ts;                         /* '<Root>/Ts' */
} ExtU_STO_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real32_T Ealpha_hat;                 /* '<Root>/Ealpha_hat' */
  real32_T Ebeta_hat;                  /* '<Root>/Ebeta_hat' */
} ExtY_STO_T;

/* Real-time Model Data Structure */
struct tag_RTM_STO_T {
  const char_T * volatile errorStatus;
};

/* Block states (default storage) */
extern DW_STO_T STO_DW;

/* External inputs (root inport signals with default storage) */
extern ExtU_STO_T STO_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_STO_T STO_Y;

/* Model entry point functions */
extern void STO_initialize(void);
extern void STO_step(void);
extern void STO_terminate(void);

/* Real-time Model object */
extern RT_MODEL_STO_T *const STO_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'STO'
 * '<S1>'   : 'STO/Subsystem'
 * '<S2>'   : 'STO/Subsystem/PLL'
 * '<S3>'   : 'STO/Subsystem/PLL/PID Controller2'
 * '<S4>'   : 'STO/Subsystem/PLL/PID Controller2/Anti-windup'
 * '<S5>'   : 'STO/Subsystem/PLL/PID Controller2/D Gain'
 * '<S6>'   : 'STO/Subsystem/PLL/PID Controller2/Filter'
 * '<S7>'   : 'STO/Subsystem/PLL/PID Controller2/Filter ICs'
 * '<S8>'   : 'STO/Subsystem/PLL/PID Controller2/I Gain'
 * '<S9>'   : 'STO/Subsystem/PLL/PID Controller2/Ideal P Gain'
 * '<S10>'  : 'STO/Subsystem/PLL/PID Controller2/Ideal P Gain Fdbk'
 * '<S11>'  : 'STO/Subsystem/PLL/PID Controller2/Integrator'
 * '<S12>'  : 'STO/Subsystem/PLL/PID Controller2/Integrator ICs'
 * '<S13>'  : 'STO/Subsystem/PLL/PID Controller2/N Copy'
 * '<S14>'  : 'STO/Subsystem/PLL/PID Controller2/N Gain'
 * '<S15>'  : 'STO/Subsystem/PLL/PID Controller2/P Copy'
 * '<S16>'  : 'STO/Subsystem/PLL/PID Controller2/Parallel P Gain'
 * '<S17>'  : 'STO/Subsystem/PLL/PID Controller2/Reset Signal'
 * '<S18>'  : 'STO/Subsystem/PLL/PID Controller2/Saturation'
 * '<S19>'  : 'STO/Subsystem/PLL/PID Controller2/Saturation Fdbk'
 * '<S20>'  : 'STO/Subsystem/PLL/PID Controller2/Sum'
 * '<S21>'  : 'STO/Subsystem/PLL/PID Controller2/Sum Fdbk'
 * '<S22>'  : 'STO/Subsystem/PLL/PID Controller2/Tracking Mode'
 * '<S23>'  : 'STO/Subsystem/PLL/PID Controller2/Tracking Mode Sum'
 * '<S24>'  : 'STO/Subsystem/PLL/PID Controller2/postSat Signal'
 * '<S25>'  : 'STO/Subsystem/PLL/PID Controller2/preSat Signal'
 * '<S26>'  : 'STO/Subsystem/PLL/PID Controller2/Anti-windup/Back Calculation'
 * '<S27>'  : 'STO/Subsystem/PLL/PID Controller2/Anti-windup/Cont. Clamping Ideal'
 * '<S28>'  : 'STO/Subsystem/PLL/PID Controller2/Anti-windup/Cont. Clamping Parallel'
 * '<S29>'  : 'STO/Subsystem/PLL/PID Controller2/Anti-windup/Disabled'
 * '<S30>'  : 'STO/Subsystem/PLL/PID Controller2/Anti-windup/Disc. Clamping Ideal'
 * '<S31>'  : 'STO/Subsystem/PLL/PID Controller2/Anti-windup/Disc. Clamping Parallel'
 * '<S32>'  : 'STO/Subsystem/PLL/PID Controller2/Anti-windup/Passthrough'
 * '<S33>'  : 'STO/Subsystem/PLL/PID Controller2/D Gain/Disabled'
 * '<S34>'  : 'STO/Subsystem/PLL/PID Controller2/D Gain/External Parameters'
 * '<S35>'  : 'STO/Subsystem/PLL/PID Controller2/D Gain/Internal Parameters'
 * '<S36>'  : 'STO/Subsystem/PLL/PID Controller2/Filter/Cont. Filter'
 * '<S37>'  : 'STO/Subsystem/PLL/PID Controller2/Filter/Differentiator'
 * '<S38>'  : 'STO/Subsystem/PLL/PID Controller2/Filter/Disabled'
 * '<S39>'  : 'STO/Subsystem/PLL/PID Controller2/Filter/Disc. Backward Euler Filter'
 * '<S40>'  : 'STO/Subsystem/PLL/PID Controller2/Filter/Disc. Forward Euler Filter'
 * '<S41>'  : 'STO/Subsystem/PLL/PID Controller2/Filter/Disc. Trapezoidal Filter'
 * '<S42>'  : 'STO/Subsystem/PLL/PID Controller2/Filter ICs/Disabled'
 * '<S43>'  : 'STO/Subsystem/PLL/PID Controller2/Filter ICs/External IC'
 * '<S44>'  : 'STO/Subsystem/PLL/PID Controller2/Filter ICs/Internal IC - Differentiator'
 * '<S45>'  : 'STO/Subsystem/PLL/PID Controller2/Filter ICs/Internal IC - Filter'
 * '<S46>'  : 'STO/Subsystem/PLL/PID Controller2/I Gain/Disabled'
 * '<S47>'  : 'STO/Subsystem/PLL/PID Controller2/I Gain/External Parameters'
 * '<S48>'  : 'STO/Subsystem/PLL/PID Controller2/I Gain/Internal Parameters'
 * '<S49>'  : 'STO/Subsystem/PLL/PID Controller2/Ideal P Gain/External Parameters'
 * '<S50>'  : 'STO/Subsystem/PLL/PID Controller2/Ideal P Gain/Internal Parameters'
 * '<S51>'  : 'STO/Subsystem/PLL/PID Controller2/Ideal P Gain/Passthrough'
 * '<S52>'  : 'STO/Subsystem/PLL/PID Controller2/Ideal P Gain Fdbk/Disabled'
 * '<S53>'  : 'STO/Subsystem/PLL/PID Controller2/Ideal P Gain Fdbk/External Parameters'
 * '<S54>'  : 'STO/Subsystem/PLL/PID Controller2/Ideal P Gain Fdbk/Internal Parameters'
 * '<S55>'  : 'STO/Subsystem/PLL/PID Controller2/Ideal P Gain Fdbk/Passthrough'
 * '<S56>'  : 'STO/Subsystem/PLL/PID Controller2/Integrator/Continuous'
 * '<S57>'  : 'STO/Subsystem/PLL/PID Controller2/Integrator/Disabled'
 * '<S58>'  : 'STO/Subsystem/PLL/PID Controller2/Integrator/Discrete'
 * '<S59>'  : 'STO/Subsystem/PLL/PID Controller2/Integrator ICs/Disabled'
 * '<S60>'  : 'STO/Subsystem/PLL/PID Controller2/Integrator ICs/External IC'
 * '<S61>'  : 'STO/Subsystem/PLL/PID Controller2/Integrator ICs/Internal IC'
 * '<S62>'  : 'STO/Subsystem/PLL/PID Controller2/N Copy/Disabled'
 * '<S63>'  : 'STO/Subsystem/PLL/PID Controller2/N Copy/Disabled wSignal Specification'
 * '<S64>'  : 'STO/Subsystem/PLL/PID Controller2/N Copy/External Parameters'
 * '<S65>'  : 'STO/Subsystem/PLL/PID Controller2/N Copy/Internal Parameters'
 * '<S66>'  : 'STO/Subsystem/PLL/PID Controller2/N Gain/Disabled'
 * '<S67>'  : 'STO/Subsystem/PLL/PID Controller2/N Gain/External Parameters'
 * '<S68>'  : 'STO/Subsystem/PLL/PID Controller2/N Gain/Internal Parameters'
 * '<S69>'  : 'STO/Subsystem/PLL/PID Controller2/N Gain/Passthrough'
 * '<S70>'  : 'STO/Subsystem/PLL/PID Controller2/P Copy/Disabled'
 * '<S71>'  : 'STO/Subsystem/PLL/PID Controller2/P Copy/External Parameters Ideal'
 * '<S72>'  : 'STO/Subsystem/PLL/PID Controller2/P Copy/Internal Parameters Ideal'
 * '<S73>'  : 'STO/Subsystem/PLL/PID Controller2/Parallel P Gain/Disabled'
 * '<S74>'  : 'STO/Subsystem/PLL/PID Controller2/Parallel P Gain/External Parameters'
 * '<S75>'  : 'STO/Subsystem/PLL/PID Controller2/Parallel P Gain/Internal Parameters'
 * '<S76>'  : 'STO/Subsystem/PLL/PID Controller2/Parallel P Gain/Passthrough'
 * '<S77>'  : 'STO/Subsystem/PLL/PID Controller2/Reset Signal/Disabled'
 * '<S78>'  : 'STO/Subsystem/PLL/PID Controller2/Reset Signal/External Reset'
 * '<S79>'  : 'STO/Subsystem/PLL/PID Controller2/Saturation/Enabled'
 * '<S80>'  : 'STO/Subsystem/PLL/PID Controller2/Saturation/Passthrough'
 * '<S81>'  : 'STO/Subsystem/PLL/PID Controller2/Saturation Fdbk/Disabled'
 * '<S82>'  : 'STO/Subsystem/PLL/PID Controller2/Saturation Fdbk/Enabled'
 * '<S83>'  : 'STO/Subsystem/PLL/PID Controller2/Saturation Fdbk/Passthrough'
 * '<S84>'  : 'STO/Subsystem/PLL/PID Controller2/Sum/Passthrough_I'
 * '<S85>'  : 'STO/Subsystem/PLL/PID Controller2/Sum/Passthrough_P'
 * '<S86>'  : 'STO/Subsystem/PLL/PID Controller2/Sum/Sum_PD'
 * '<S87>'  : 'STO/Subsystem/PLL/PID Controller2/Sum/Sum_PI'
 * '<S88>'  : 'STO/Subsystem/PLL/PID Controller2/Sum/Sum_PID'
 * '<S89>'  : 'STO/Subsystem/PLL/PID Controller2/Sum Fdbk/Disabled'
 * '<S90>'  : 'STO/Subsystem/PLL/PID Controller2/Sum Fdbk/Enabled'
 * '<S91>'  : 'STO/Subsystem/PLL/PID Controller2/Sum Fdbk/Passthrough'
 * '<S92>'  : 'STO/Subsystem/PLL/PID Controller2/Tracking Mode/Disabled'
 * '<S93>'  : 'STO/Subsystem/PLL/PID Controller2/Tracking Mode/Enabled'
 * '<S94>'  : 'STO/Subsystem/PLL/PID Controller2/Tracking Mode Sum/Passthrough'
 * '<S95>'  : 'STO/Subsystem/PLL/PID Controller2/Tracking Mode Sum/Tracking Mode'
 * '<S96>'  : 'STO/Subsystem/PLL/PID Controller2/postSat Signal/Feedback_Path'
 * '<S97>'  : 'STO/Subsystem/PLL/PID Controller2/postSat Signal/Forward_Path'
 * '<S98>'  : 'STO/Subsystem/PLL/PID Controller2/preSat Signal/Feedback_Path'
 * '<S99>'  : 'STO/Subsystem/PLL/PID Controller2/preSat Signal/Forward_Path'
 */
#endif                                 /* RTW_HEADER_STO_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
