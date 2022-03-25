#include <stdio.h>
int main(void)
{
    int num = 10;
    int *p;
    p = &num;
    
    printf("num'address = %u\n", &num);
    printf("pointer'value = %u\n", p);
    printf("num'value = %d\n", num);
    printf("pointing value = %d\n", &num);

    return 0;
}