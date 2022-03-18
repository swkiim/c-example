#include<stdio.h>

int main(void)
{
    double pheight = 0.001;
    const double everest = 8800.0;
    const double baekdu = 2750.0;
    int count = 0;
    
    while(pheight < everest){
        while(pheight < baekdu){
            pheight *= 2.0;
            count++;
            if (pheight > baekdu){
            printf("Higher than Baekdu Mountain : Folding count is %d \n\n",count);
            printf("Height = %lfM\n\n", pheight);
            }
        } 
        pheight *= 2.0;
        count++;
    }
    printf("Higher than Everest Mountain : Folding count is %d \n\n",count);
    printf("Height = %lfM", pheight);
    
    return 0;
}