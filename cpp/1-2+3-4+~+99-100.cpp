#include<stdio.h>

int main(void)
{
    int sum = 0;
    for(int i = 1; i <= 100; i++)
    {
        if(i % 2 == 1)
        {
            sum += i;
        }
        else
        {
            sum -= i;
        }
    }
    printf("sum = %d\n", sum);
    return 0;
}