#include <stdio.h>
int main(void)
{
        int a[] = {10,20,30,4,5};
        printf("List name a=%u *a=%d\n", a, *a);
        printf("List name's address &a=%u \n", &a);
        return 0;
}