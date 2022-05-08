#include <stdio.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string>
#define MAXNUM 10
using namespace std;
#define portno 9000
#define NUM_LENGTH 8

void error(char *msg)
{
	perror(msg);
	exit(1);
}

int main (int argc, char *argv[])
{
	int sockfd, clilen, len, retval;
	struct sockaddr_in server_addr, clientaddr;
	char buf[64], rcv_buf[64];
	char serverIP[14];
	printf("input server IP : ");
	
	scanf("%s", serverIP);
	printf("using port #%d ip = %s\n", portno, serverIP);
	
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0)
		error(const_cast < char * > ("ERROR opening socket"));
	bzero((char *) &server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	printf("UDP 1 num...\n");
	server_addr.sin_addr.s_addr = inet_addr(serverIP);
	printf("UDP 2 num...\n");
	server_addr.sin_port = htons(portno);
	printf("UDP 3 num...\n");
	
	while(1)
	{
		clilen = sizeof(clientaddr);
		printf("\n[점수요청학생 학번] ");
		scanf("%s", buf);
		len = strlen(buf);
		if(buf[len - 1] == '\n')
			buf[len - 1] = '\0';
		if(strlen(buf) < NUM_LENGTH)
		{
			printf("wrong student number\n");
			break;
		}
		
		retval = sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
		if (retval == 0)
		{
			close(sockfd);
			printf("socket closed = %d\n", sockfd);
			break;
		}
		printf("[학번] %d 성적조회 요청했습니다.\n", atoi(buf));
		
		retval = recvfrom(sockfd, rcv_buf, BUFSIZ, 0, (struct sockaddr *)&clientaddr, (socklen_t*)&clilen);
		printf("rcv 1 %d\n", retval);
		if ((retval) < 0)
		{
			printf("rcv 2 %d\n", retval);
			error(const_cast < char * > ("ERROR reading from socket"));
		}
		if (memcmp(&clientaddr, &server_addr, sizeof(clientaddr)))
		{
			printf("[오류] 잘못된 데이터입니다!\n");
			continue;
		}
		
		rcv_buf[retval] = '\0';
		printf("[시험 성적조회] %s 점입니다.\n", rcv_buf);
		break;
	}
	close(sockfd);
	return 0;
}