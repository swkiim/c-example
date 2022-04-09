#include<stdio.h>
int main(void)
{
    double meter, meter2;
    int i = 0;

    while (i < 3)
    {
        meter = i * 1609;
        meter2 = i * 0.0254;
        printf("%d miles is %lf meters\n", i, meter);
        printf("%d inches is %lf meters\n", i, meter2);

        i++;
    }
    return 0;
}