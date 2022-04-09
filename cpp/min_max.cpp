#include<stdio.h>
#define SIZE 10

int main(void)
{
    int prices[SIZE] = {12, 3, 19, 6, 18, 8, 12, 4, 1, 19};
    int i, min, max;

    printf("[ ");
    for(i = 0; i < SIZE; i++){
        printf("%d ", prices[i]);
    }
    printf("]\n");

    min = prices[0];

    for(i = 1; i < SIZE; i++){
        max = prices[i];

        if(prices[i] < min)
           min = prices[i];
    }
    printf("maximum number is %d. \n", max);
    printf("minimum number is %d.\n", min);
    
    return 0;
}