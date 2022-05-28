#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <wiringPi.h>

int TRIG = 28; //gpio 21 pin 40
int ECHO = 29; //gpio 20 pin 38

static float Echo_Test(){
	unsigned long TX_time = 0;
	unsigned long RX_time = 0;
	float distance = 0;
	unsigned long timeout = 50000000; //0.5sec ~ 171m (50 * 10^6)us
	unsigned long Wait_time = micros();
	
	pinMode(TRIG, OUTPUT); //gpio 21 pin 40 using trigger
	pinMode(ECHO, INPUT); //gpio 20 pin 38 using Echo ultra sound
	
	//Ensure trigger is low
	digitalWrite(TRIG, LOW);
	delay(50); //milli second
	
	//Trigger tx sound
	digitalWrite(TRIG, HIGH);
	delayMicroseconds(10); //micro second
	digitalWrite(TRIG, LOW);
	
	//Wait for tx response, or timeout
	while((digitalRead(ECHO) == LOW && (micros() - Wait_time) < timeout)){
		if(digitalRead(ECHO) == HIGH) break;
	}
	
	//Cancel on timeout
	if((micros() - Wait_time) > timeout){
		printf("0.out of range.micros = %d wait_time = %ld\n", micros(), Wait_time);
	}
	
	TX_time = micros();
	
	//Wait for rx sound respose, or timeout
	while((digitalRead(ECHO) == HIGH && (micros() - Wait_time)) < timeout){
		if(digitalRead(ECHO) == LOW) break;
	}
	
	//Cancel on timeout
	if((micros() - Wait_time) > timeout){
		printf("1. Out of range.\n");
	}
	
	RX_time = micros();
	
	//Calculate rx-tx duration to chane distance
	distance = (float)(RX_time - TX_time) * 0.017;
	
	return distance;
}

int main(){
	float distance = 0;
	printf("HC-SR04 Ultrasonic distance measure program \n");
	if(wiringPiSetup() == -1){
		exit(EXIT_FAILURE);
	}
	if(setuid(getuid()) < 0){
		printf("Dropping privileges failed.\n");
		exit(EXIT_FAILURE);
	}
	for(;;){
		distance = Echo_Test();
		printf("Distance %.2f cm.\n", distance);
		delay(500);
	}
	return 0;
}
