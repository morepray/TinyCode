#include "stdio.h"

int main()
{
    int releasetime_year;
    int releasetimemonth;
    int releasetimeday;
    // scanf("%d %d %d", &releasetime_year, &releasetimemonth, &releasetimeday);

    int current_time_year;
    int current_time_month;
    int current_time_day;
    // scanf("%d %d %d", &current_time_year, &current_time_month, &current_time_day);
    while (scanf("%d", &current_time_year))
    {
        printf("the result is = %d\n", current_time_year);
    }


    printf("%d %d %d\n", releasetime_year, releasetimemonth, releasetimeday);
    return 0;
}