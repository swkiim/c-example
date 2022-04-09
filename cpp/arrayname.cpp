#include <stdio.h>
int main(void)
{
        int a[] = {10,20,30,40,50};
        int *p;
        p=a;
        printf("array name a0=%d a1=%d a2=%d\n", a[0],a[1],a[2]);
        printf("array name p0=%d  p1=%d p2=%d\n", p[0], p[1], p[2]);
        return 0;
}
