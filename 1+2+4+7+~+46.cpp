#include <stdio.h>

int main(void)
{
    int sum = 0;
    int inc = 1;
    int val = 1;
    int tmp;
    for(int i = 1; i <= 10; i++)
    {
        if(i > 1)
        {
            inc += 2;
            tmp = inc;
            val += tmp;
        }
        if(i == 10)
        {
            printf("%d", val);
        }
        else
        {
            printf("%d ", val);
        }
    }
    return 0;
}