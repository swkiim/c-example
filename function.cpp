#include<stdio.h>

int add(int x, int y);
int differ(int a, int b);

int main()
{
    int i, j, sum, minus;

    printf("Insert two numbers : ");
    scanf("%d %d", &i, &j);

    sum = add(i, j);
    minus = differ(i, j);

    printf("sum : %d + %d = %d\n", i, j, sum);
    printf("minus : %d - %d = %d", i, j, minus);

    return 0;
}

int add(int x, int y)
{
    int result;
    result = x + y;
    return result;
}

int differ(int a, int b)
{
    int result;
    result = a - b;
    return result;
}