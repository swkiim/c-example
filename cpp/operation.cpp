#include <stdio.h>
int main(void)
{
    int x, y;

    x = 1;
    y = ++x;
    printf("x = %d, y = %d\n", x, y);

    y = x++;
    printf("x = %d, y = %d\n", x, y);

    return 0;
}