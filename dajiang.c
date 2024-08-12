#include <stdio.h>
int main()
{
    int a[5] = {1, 2, 3, 4, 5};
    int *p = (int *)(&a + 1);
    printf("%d\n", *(&a));
    printf("%d\n", *(a + 1));
    printf("%d\n", *p);
    printf("%d\n", *(p - 1));
    printf("%d%d", *(a + 1), *(p - 1));
    return 0;
}
