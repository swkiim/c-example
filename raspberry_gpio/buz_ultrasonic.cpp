#include <stdio.h>
#include <wiringPi.h>
#include <softTone.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>

#define buzzerp 25
#define LED 27

int octav[3] = {200, 800, 2000};

double Echo_Test();

int main(){
	double distance = 0;
	int cnt = 0;
	int i;
	
	if(wiringPiSetup() == -1) return 1;
	pinMode(buzzerp, OUTPUT);
	pinMode(LED, OUTPUT);
	
	softToneCreate(buzzerp);
	printf("main running!!\n");
	
	for(i = 0; i < 3; i++){
		softToneWrite(buzzerp, octav[i]);
		delay(100);
	}
	for(;;){
		softToneWrite(buzzerp, 0);
		distance = Echo_Test();
		printf("Distance : %d %.2f cm.\n", cnt, distance);
		cnt++;
		if(distance < 20) softToneWrite(buzzerp, 2000);
		else if(distance < 50 && distance >=20) softToneWrite(buzzerp, 1000);
		else if(distance >= 50 && distance <100) softToneWrite(buzzerp, 200);
		else softToneWrite(buzzerp, 0);
		delay(500);
	}
	return 0;
}
