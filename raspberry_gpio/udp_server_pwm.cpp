#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <wiringPi.h>
#define MAXNUM 10

void led_on()
{
	digitalWrite(29, 0);
}

void led_off()
{
	digitalWrite(29, 1);
}

void buzzer_on()
{
	digitalWrite(28, 0);
}

void buzzer_off()
{
	digitalWrite(28, 1);
}

void error( char *msg)
{
	perror( msg );
	exit(1);
}
int main(int argc, char *argv[])
{
	int sockfd, portno = 9000, clilen;
	struct sockaddr_in serv_addr, clientaddr;
	char buf[64];
	printf( "using port %d/n", portno );
	
	if (wiringPiSetup() == -1)
	{
		return -1;
	}
	pinMode(29, OUTPUT);
	pinMode(28, OUTPUT);
		
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0)
		error( const_cast < char * >("ERROR opening soc") );
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons( portno );
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		error( const_cast < char * >( "ERROR on binding" ) );
	while(1)
	{
		int retval = 99;
		int addrlen;
		printf(" UDP Server waiting for client...\n");
		while(1){
			clilen = sizeof(clientaddr);
			retval = recvfrom(sockfd, buf, 64, 0, (struct sockaddr *)&clientaddr, (socklen_t*)&clilen);
			printf( "rcv1 %d \n", retval);
			if ((retval) < 0)
			{
				printf("rcv2 %d \n", retval);
				error(const_cast < char * >("ERROR from socket"));
			}
			else if (retval > 0)
			{
				buf[retval] = '\0';
				printf("got %s size = %d \n", buf, retval);
				if(buf[0] == 'q')
				{
					close(sockfd);
					printf("socket closed = %d\n", sockfd);
					break;
				}
				else if(buf[0] == '1')
				{
					led_off();
					break;
				}
				else if(buf[0] == '2')
				{
					led_on();
					break;
				}
				else if(buf[0] == '3')
				{
					buzzer_off();
				}
				else if(buf[0] == '4')
				{
					buzzer_on();
				}
				
				printf("sending back %s\n", buf);
				retval = sendto(sockfd, buf, retval, 0, (struct sockaddr *)&clientaddr, sizeof(clientaddr));
			}
			else if (retval == 0)
			{
				close(sockfd);
				printf("socket closed = %d\n", sockfd);
				break;
			}
		}
	}
	close(sockfd);
	return 0;
}