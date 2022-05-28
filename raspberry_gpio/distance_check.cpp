#include <stdio.h>
#include <wiringPi.h>
#include <softTone.h>
#include <time.h>

#define buzzerp 25
#define LED 26

int octav[3] = {200, 800, 2000};

double Echo_Test();
void GetLocalIPAddress(char *sIPAddress);
char gsIPv4Address[20];

int main(){
	double distance = 0;
	int cnt = 0;
	int i;
	time_t timer;
	struct tm *ctm;
	
	if(wiringPiSetup() == -1) return 1;
	pinMode(buzzerp, OUTPUT);
	pinMode(LED, OUTPUT);
	
	softToneCreate(buzzerp);
	printf("main running!!\n");
	GetLocalIPAddress(gsIPv4Address);
	printf("my ip %s.\n", gsIPv4Address);
	
	for(i = 0; i < 3; i++){
		softToneWrite(buzzerp, octav[i]);
		delay(100);
	}
	for(;;){
		softToneWrite(buzzerp, 0);
		timer = time(NULL);
		ctm = localtime(&timer);
		printf("%d %d:%d:%d -> ", ctm->tm_mday, ctm->tm_hour, ctm->tm_min, ctm->tm_sec);
		
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
