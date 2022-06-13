#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <wiringPi.h>
#include <pthread.h>

int main(){
	time_t ref;
	struct tm *d;
	for(;;){
		ref = time(NULL);
		d = localtime(&ref);
		system("sudo ls");
		system("feh DISPLAY=:0.0 XAUTHORITY=/home/pi/.Xauthority/usr/bin/feh -q -p -Z -F -R 60 -Y -D 2.0 /home/pi/picture/");
		printf("system test %2d : %2d : %2d\n", d->tm_hour, d->tm_min, d->tm_sec);
		sleep(1);
		delay(1000);
	}
	return 0;
}
