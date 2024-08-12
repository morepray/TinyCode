#include "stdint.h"
#include "stdio.h"
#include "math.h"

#define MPCC_PWM_PERIOD (14999)
#define MPCC_RS (0.125f)
#define MPCC_LS (0.00011f)
#define MPCC_FLUX (0.003749f)
#define MPCC_TPWM (0.0000625f)
#define MPCC_VBUS (24.0f)
#define MPCC_SQRT3 (1.732050807568877f)

typedef struct
{
    float Vd_Last;
    float Vq_Last;
    float Idpre;
    float Iqpre;
    float Error;

    uint8_t Sector;
} MPCC_t;

typedef struct
{
    float alfa;
    float beta;
} Voltage_Vector_t;

typedef struct
{
    uint32_t CntChA;
    uint32_t CntChB;
    uint32_t CntChC;
} SwitchOutput_t;

extern MPCC_t MPCC_M1;

void MPCC_Init(void);
void MPCC_Reset(void);
SwitchOutput_t MPCC_TaskHandle(float Idref, float Iqref, float Id, float Iq, float We, float Theta);

MPCC_t MPCC_M1 = {
    .Vd_Last = 0.0f,
    .Vq_Last = 0.0f,
    .Idpre = 0.0f,
    .Iqpre = 0.0f,
    .Sector = 0,
    .Error = 0,
};

Voltage_Vector_t VoltageVector[8] = {
    {.alfa = 0.0f, .beta = 0.0f},
    {.alfa = 2.0f * MPCC_VBUS / 3.0f, .beta = 0.0f},
    {.alfa = 1.0f * MPCC_VBUS / 3.0f, .beta = MPCC_VBUS / MPCC_SQRT3},
    {.alfa = -1.0f * MPCC_VBUS / 3.0f, .beta = MPCC_VBUS / MPCC_SQRT3},
    {.alfa = -2.0f * MPCC_VBUS / 3.0f, .beta = 0.0f},
    {.alfa = -1.0f * MPCC_VBUS / 3.0f, .beta = -MPCC_VBUS / MPCC_SQRT3},
    {.alfa = 1.0f * MPCC_VBUS / 3.0f, .beta = -MPCC_VBUS / MPCC_SQRT3},
    {.alfa = 0.0f, .beta = 0.0f},
};

Voltage_Vector_t Vdqtemp[8];

SwitchOutput_t SwitchTable[8] = {
    {0, 0, 0},
    {1, 0, 0},
    {1, 1, 0},
    {0, 1, 0},
    {0, 1, 1},
    {0, 0, 1},
    {1, 0, 1},
    {0, 0, 0},
};

void MPCC_Init(void)
{
    MPCC_Reset();
}

void MPCC_Reset(void)
{
    MPCC_M1.Vd_Last = 0.0f;
    MPCC_M1.Vq_Last = 0.0f;
    MPCC_M1.Idpre = 0.0f;
    MPCC_M1.Iqpre = 0.0f;
    MPCC_M1.Sector = 0;
    MPCC_M1.Error = 0.0f;
}

float MPCC_Temp1 = (1.0f - MPCC_TPWM * MPCC_RS / MPCC_LS);
/**
 * @brief 单矢量MPCC任务函数
 *
 * @param Idref
 * @param Iqref
 * @param Id
 * @param Iq
 * @param We
 * @param Theta
 */
float IdCompen_scope = 0;
float IqCompen_scope = 0;
SwitchOutput_t MPCC_TaskHandle(float Idref, float Iqref, float Id, float Iq, float We, float Theta)
{
    float IdCompen, IqCompen;
    float hCost = (float)2147483647.0f, Error = 0;
    float Vdtemp, Vqtemp;
    float IdPre, IqPre;
    uint8_t i = 0, Sector = 0;
    SwitchOutput_t TIM_CCR;

    /* 电流补偿 */
    IdCompen = MPCC_Temp1 * Id + MPCC_TPWM * (We * Iq + MPCC_M1.Vd_Last / MPCC_LS);
    IqCompen = MPCC_Temp1 * Iq + MPCC_TPWM * (-We * Id + MPCC_M1.Vq_Last / MPCC_LS - We * MPCC_FLUX / MPCC_LS);
    IdCompen_scope = IdCompen;
    IqCompen_scope = IqCompen;

    float arm_cos_temp = cos(Theta);
    float arm_sin_temp = sin(Theta);
    for (i = 0; i < 8; i++)
    {
        Vdtemp = VoltageVector[i].alfa * arm_cos_temp + VoltageVector[i].beta * arm_sin_temp;
        Vqtemp = -VoltageVector[i].alfa * arm_sin_temp + VoltageVector[i].beta * arm_cos_temp;

        IdPre = MPCC_Temp1 * IdCompen + MPCC_TPWM * (We * IqCompen + Vdtemp / MPCC_LS);
        IqPre = MPCC_Temp1 * IqCompen + MPCC_TPWM * (-We * IdCompen + Vqtemp / MPCC_LS - We * MPCC_FLUX / MPCC_LS);
        // printf("%f\n", IdPre);
        // printf("%f\n", IdPre);
        // printf("\n");
        Error = (Idref - IdPre) * (Idref - IdPre) + (Iqref - IqPre) * (Iqref - IqPre);

        Vdqtemp[i].alfa = Vdtemp;
        Vdqtemp[i].beta = Vqtemp;
        if (Error < hCost)
        {
            hCost = Error;
            Sector = i;

            MPCC_M1.Error = Error;
            MPCC_M1.Vd_Last = Vdtemp;
            MPCC_M1.Vq_Last = Vqtemp;
            MPCC_M1.Sector = Sector;
            MPCC_M1.Idpre = IdPre;
            MPCC_M1.Iqpre = IqPre;
        }
    }
    printf("%d\n", Sector);

    TIM_CCR.CntChA = (uint32_t)SwitchTable[Sector].CntChA * ((uint32_t)MPCC_PWM_PERIOD);
    TIM_CCR.CntChB = (uint32_t)SwitchTable[Sector].CntChB * ((uint32_t)MPCC_PWM_PERIOD);
    TIM_CCR.CntChC = (uint32_t)SwitchTable[Sector].CntChC * ((uint32_t)MPCC_PWM_PERIOD);

    return TIM_CCR;
}

int main()
{
    for (uint32_t i = 0; i < 100; i++)
    {
        /* code */
        MPCC_TaskHandle(0, 2, 0, 0, i, 0);
    }
}