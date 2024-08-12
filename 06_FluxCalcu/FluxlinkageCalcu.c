#include "stdio.h"
#include "math.h"

#define Mm_PI (3.14159265358979323846)

int main()
{
    float flux; // 磁链，单位：Wb
    float E;    // 空载相反电动势 ，单位：V
    float E1;   // 相反电动势有效值 ，单位：Vrms
    float We;   // 定子电角频率，单位：rad / s
    float N;    // N：转速，单位：rpm
    float F;    // F：基波频率，单位：HZ
    float P;    // P：极对数，不是极数
    float Ke;   // 空载相反电动势系数，Vrms/rpm

    float Pn = 5.0f;
    float Vpp = 6.8f; // 示波器测量的峰峰值
    float Ts = 0.02f; //

    Ke = 1000.0f * Pn * Vpp * Ts / 120.0f / sqrt(3);
    /* 当用示波器测得Vpp和Ts时，使用公式 */
    flux = Ke * 3.0f / 100.0f / Mm_PI / Pn;
    printf("-------\n");
    printf("Ke\t= %.8f(Vrms/krpm).\n", Ke);
    printf("Flux\t= %.8f(Web).\nMatlab\t= %.8f(Web).\n", flux, flux / sqrt(3));
    printf("-------\n");
    return 0;
}