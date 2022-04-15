#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <softTone.h>
#define led 28 // GPIO 번
int octav[22] = {0, 131, 147, 165, 175, 196, 220, 247,262, 294, 330,350, 392, 440, 494,524, 588, 659, 699, 784, 880, 988}; // 21Frequency
int main (void)
{
    if (wiringPiSetup () == -1)
        return 1 ;
    pinMode (led, OUTPUT) ;
    softToneCreate (led) ;
    softPwmCreate(led,0,100);
    int volumn=1;
    for (;;)
    {
        int i;
        for (i=0;i<10;i++) {
        softPwmWrite(led,i*10);
        delay (500) ;
    }
    digitalWrite(led,0);
    delay(500);
    printf(" sencond play volumn\n");
    for (i=1;i<20;i++){
        softPwmWrite(led,volumn);
        volumn=volumn+5;
        delay (100) ;
    }
    printf(" third \n");
    digitalWrite(led,0);
    }
    return 0 ;
}
