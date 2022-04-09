#include <stdio.h>

int main()
{
    int i, k = 0, j;
    int a[5][5] = {0};
    for(j = 0; j < 3; j++)
    {
        for(i = 2 - j; i <= j + 2; i++)
        {
            ++k;
            a[j][i] = k;
        }
    }
    for(j = 3; j < 5; j++)
    {
        for(i = j - 2; i <= 6 - j; i++)
        {
            ++k;
            a[j][i] = k;
        }
    }
    for(int x = 0; x <= 4; x++)
    {
        for(int y = 0; y <= 4; y++)
        {
            if(a[x][y])
                printf("%5d", a[x][y]);
            else
                printf("  .  ");
        }
        printf("\n");
    }
    return 0;
}