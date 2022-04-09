#include <wiringPi.h>

int main()
{
    if(wiringPiSetup() ==  -1)
        return 1;
    pinMode(21, OUTPUT);
    pinMode(22, OUTPUT);
    for(int i = 0; i < 5; i++)
    {
        digitalWirite(21, 0);
        delay(500);
        digitalWirite(21, 1);
        delay(500);
        digitalWirite(22, 0);
        delay(500);
        digitalWirite(22, 1);
        delay(500);
    }
    return 0;
}