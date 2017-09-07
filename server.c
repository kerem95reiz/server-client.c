#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include<netinet/in.h>
#define PORT 9002
#define REQ 5
int main(){
char server_message[256]="You reached the server!";
//create the aerver socket
int server_socket;
server_socket=socket(AF_INET,SOCK_STREAM,0);
		if(server_socket<0)
		{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}
//define the server address 
struct sockaddr_in server_address;
server_address.sin_port=htons(PORT);
server_address.sin_family=AF_INET;
server_address.sin_addr.s_addr=INADDR_ANY;//any ip on local

// bind the socket to specified ip and port
if(bind(server_socket,(struct sockaddr*) &server_address,sizeof(server_address))<0)
{
	printf("bind error\n");
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
if(listen(server_socket,REQ)<0)//REQ request can handle at a time
{printf("listen error\n");
		perror("listen");
		exit(EXIT_FAILURE);
	} 
int client_socket;
client_socket=accept(server_socket,NULL,NULL);
send(client_socket,server_message,sizeof(server_message),0);
close(server_socket);
return 0;
}
