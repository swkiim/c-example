#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <wiringPi.h>
#include <sys/socket.h>
#include <netdb.h>
#include <softTone.h>

#define BUZZER 25
#define Echo_Test_ON 100
#define Echo_Test_OFF 99

int octav[3] = {200, 800, 2000};

char RUN_FLAG = 0;
void* udps(void* arg);
void RUN_Echo_test();

double Echo_Test();

char message[30] = "start udps communication!";
int main(){	
	if(wiringPiSetup() == -1) return 1;
	
	pinMode(BUZZER, OUTPUT);
	softToneCreate(BUZZER);
	
	int res;
	pthread_t udp_thread;
	res = pthread_create(&udp_thread, NULL, udps, (void*)message);
	if(res != 0){
		printf("Thread creation failed");
		exit(EXIT_FAILURE);
	}
	printf("Waiting for thread to finish...\n");
	if(res != 0){
		printf("Thread join failed");
		exit(EXIT_FAILURE);
	}
	for(int i = 0; i < 1000 ;i++){
		printf("main --> %s\n", message);
		if(RUN_FLAG == Echo_Test_ON){
			RUN_Echo_test();
		}
		if(RUN_FLAG == 1){
			printf("exit process is running\n");
			break;
		}
		delay(500);
	}
	return 0;
}

void* udps(void* arg){
	
	
	printf("\n thread is running. Argument was %s\n", (char*)arg);
	strcpy(message, "thread running");
	
	int sockfd, portno = 9000, clilen;
	struct sockaddr_in serv_addr, clientaddr;
	char buf[64];
	printf("using port #%d\n", portno);
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd < 0)
		printf("ERROR opening socket");
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		printf(const_cast < char * >("ERROR on binding"));
	
	int retval = 99;
	int addrlen;
	printf("UDP Server waiting for client...\n");
	while(1){
		clilen = sizeof(clientaddr);
		retval = recvfrom(sockfd, buf, 64, 0, (struct sockaddr *)&clientaddr, (socklen_t*)&clilen);
		printf("rcv1 %d \n", retval);
		if((retval) < 0){
			printf("rcv2 %d \n",retval);
			printf(const_cast < char * >("ERROR reading from socket"));
		}else if(retval > 0){
			buf[retval] = '\0';
			printf("got %s size = %d \n", buf, retval);
			if(buf[0] == '2'){
				printf("Buzzer running\n");
				for(int i = 0; i < 2; i++){
					softToneWrite(BUZZER, 100);
					delay(500);
					softToneWrite(BUZZER, 0);
					delay(500);
				}
			}
			if(buf[0] == '3'){
				RUN_FLAG = Echo_Test_ON;
				// RUN_Echo_test();
			}
			if(buf[0] == '4'){
				RUN_FLAG = Echo_Test_OFF;
			}
			if(buf[0] == 'q'){
				printf("socket closed = %d \n", sockfd);
				RUN_FLAG = 1;
				break;
			}
			printf("sending back %s \n", buf);
			retval = sendto(sockfd, buf, retval, 0, (struct sockaddr *)&clientaddr, sizeof(clientaddr));
		}else if(retval == 0){
			close(sockfd);
			printf("socket closed = %d\n", sockfd);
			break;
		}
		delay(100);
	}
	close(sockfd);
	pthread_exit(arg);
}

void RUN_Echo_test(){
	double distance = 0;
	int cnt = 0;
	
	if(RUN_FLAG == Echo_Test_ON){
		printf("Ultrasonic working\n");
		softToneWrite(BUZZER, 0);
		distance = Echo_Test();
		printf("Distance : %d %.2f cm.\n", cnt, distance);
		cnt++;
		if(distance < 30) softToneWrite(BUZZER, 2000);
		else if(distance < 60 && distance >= 30) softToneWrite(BUZZER, 1000);
		else if(distance >= 60 && distance < 70) softToneWrite(BUZZER, 200);
		else softToneWrite(BUZZER, 0);
		delay(500);
	}else{
		RUN_FLAG = Echo_Test_OFF;
	}
}
