#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <wiringPi.h>
#include <softTone.h>
#include <pthread.h>

#define BUF_SIZE 50
#define MAX_BUF 32
#define BUZZER 25
#define Echo_Test_ON 100
#define Echo_Test_OFF 99

using namespace std;

void GetLocalIPAddress(char *sIPAddress);
char gsIPv4Address[20];

int octav[3] = {200, 800, 2000};

char RUN_FLAG = 0;
void* tcps(void* arg);
void RUN_Echo_test();

double Echo_Test();

int main(){	
	if(wiringPiSetup() == -1) return 1;
	
	pinMode(BUZZER, OUTPUT);
	softToneCreate(BUZZER);
	
	int res;
	pthread_t udp_thread;
	res = pthread_create(&udp_thread, NULL, tcps, NULL);
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
		
		if(RUN_FLAG == Echo_Test_ON){
			RUN_Echo_test();
		}
		if(RUN_FLAG == 1){
			printf("exit process is running\n");
			break;
		}
		delay(300);
	}
	return 0;
}

void* tcps(void* arg){
	int server_fd, client_fd;
	char buffer[BUF_SIZE], sendbuf[BUF_SIZE + 20];
	struct sockaddr_in server_addr, client_addr;
	char temp[20];
	int msg_size;
	socklen_t len;
	
	GetLocalIPAddress(gsIPv4Address);
	printf("my ip %s.\n", gsIPv4Address);

	if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		cout << "Server : Can't open stream socket \n";
		exit(0);
	}
	
	memset(&server_addr, 0x00, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(9000);
	
	if(bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
		cout << "Server : Can't bind local address.\n";
		exit(0);
	}
	
	if(listen(server_fd, 5) < 0){
		cout << "Server : Can't listening connect.\n";
		exit(0);
	}
	
	memset(buffer, 0x00, sizeof(buffer));
	len = sizeof(client_addr);
	cout << "Server : waiting connection request.\n";
	client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &len);
	inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, temp, sizeof(temp));
	
	cout << "Server : %s client connected.\n";

	while(1){
		if(client_fd < 0){
			cout << "Server : accept failed.\n";
		}
		msg_size = read(client_fd, buffer, 1024);
		
		sprintf(sendbuf, buffer, "->msg rcv\n");
		cout << buffer << endl;
		
		if(!strncmp(buffer, "fin", 3)){
			cout << "fin1\n";
			sprintf(sendbuf, "->msg fin rcv %s\n", buffer);
			close(server_fd);
		}
		else if(buffer[0] == '2'){
			printf("Buzzer running\n");
			for(int i = 0; i < 2; i++){
				softToneWrite(BUZZER, 100);
				delay(500);
				softToneWrite(BUZZER, 0);
				delay(500);
			}
		}
		else if(buffer[0] == '3'){
			RUN_FLAG = Echo_Test_ON;
			// RUN_Echo_test();
		}
		else if(buffer[0] == '4'){
			RUN_FLAG = Echo_Test_OFF;
			printf("Echo Test Stop\n");
		}
		else if(buffer[0] == 'q'){
			cout << "quit receive\n";
			sprintf(sendbuf, "->msg quit rcv %s\n", buffer);
			close(server_fd);
			break;
		}
		
		if(write(client_fd, sendbuf, strlen(sendbuf)) < 0){
			puts("Send failed");
		}
		
		memset(buffer, 0x00, sizeof(buffer));
		memset(sendbuf, 0x00, sizeof(sendbuf));
	}
	close(server_fd);
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
