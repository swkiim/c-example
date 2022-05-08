#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUF_SIZE 50
#define MAX_BUF 32
using namespace std;

int main(int argc, char*argv[])
{
	int server_fd, client_fd;
	char buffer[BUF_SIZE], sendbuf[BUF_SIZE];
	struct sockaddr_in server_addr, client_addr;
	char temp[20];
	int msg_size;
	socklen_t len;
	
	if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 1)
	{
		cout << "Server : Can't open stream socket \n";
		exit(0);
	}
	
	memset(&server_addr, 0x00, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(9000);
	
	if(bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
	{
		cout << "Server : Can't bind local address.\n";
		exit(0);
	}
	if(listen(server_fd, 5) < 0)
	{
		cout << "Server : Can't listening connect.\n";
		exit(0);
	}
	memset(buffer, 0x00, sizeof(buffer));
	len = sizeof(client_addr);
	cout << "Server : waiting connection request.\n";
	client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &len);
	inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, temp, sizeof(temp));
	
	cout << "Server : %s client connected.\n", temp;
	
	while(1)
	{
		if(client_fd < 0)
		{
			cout << "Server : accept failed.\n";
			return 0;
		}
		msg_size = read(client_fd, buffer, 1024);
		
		sprintf(sendbuf, buffer, "->msg rcv\n");
		cout << buffer << endl;
		
		if(!strncmp(buffer, "fin", 3))
		{
			cout << "fin\n";
			sprintf(sendbuf, buffer, "->msg fin rv\n");
			close(server_fd);
			return 0;
		}
		
		if(send(client_fd, sendbuf, strlen(sendbuf), 0) < 0)
		{
			if(write(client_fd, sendbuf, strlen(sendbuf)) < 0)
			{
				puts("Send failed");
				return 1;
			}
		}
		memset(buffer, 0x00, sizeof(buffer));
		memset(sendbuf, 0x00, sizeof(sendbuf));
	}
	close(server_fd);
	return 0;
}
