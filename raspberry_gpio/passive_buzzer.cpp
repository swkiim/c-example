#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <softTone.h>
#define buzzer 29 // GPIO number 29

int octav[22] = {0, 131, 147, 165, 175, 196, 220, 247, 262, 294, 330, 350, 392, 440, 494, 524, 588, 659, 699, 784, 880, 988}; // 21 frequency

int main(void)
{
	if (wiringPiSetup() == -1)
		return 1;

	pinMode (buzzer, OUTPUT);
	softToneCreate (buzzer);
	for(;;)
	{
		int i;
		for (i = 0; i < 10; i++)
		{
			softToneWrite (buzzer, octav[i]);
			delay(500);
		}
		for (i = 100; i < 4001; i = i +10)
		{
			softToneWrite (buzzer, i);
			delay(5);
		}
		break;
	}
	return 0;
}
