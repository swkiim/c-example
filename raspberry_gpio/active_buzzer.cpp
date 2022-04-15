#include <stdio.h>
#include <wiringPi.h>
#define buzzer 29 // GPIO num 29

int main(void)
{
	if (wiringPiSetup() == -1)
	{
		return 1;
	}
	pinMode(buzzer, OUTPUT);
	for(;;)
	{
		int i;
		for (i = 0; i < 3; i++)
		{
			printf("buzzer test1 %d \n", i);
			digitalWrite(buzzer, 1); // On
			delay(300);  // ms
			digitalWrite(buzzer, 0); // Off
			delay(300); // ms
		}
		for (i = 0; i < 2; i++)
		{
			printf("led test2 %d \n", i);
			digitalWrite(buzzer, 1); // On
			delay(600); // ms
			digitalWrite(buzzer, 0); // Off
			delay(600); // ms
		}
		break;
	}
	return 0;
}
