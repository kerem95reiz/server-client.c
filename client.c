#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include<netinet/in.h>
#define PORT 9002
int main(){
	//creating socket
	int network_socket;
	network_socket=socket(AF_INET,SOCK_STREAM,0);//domain, type, protocol
	if(network_socket<0){
	perror("Socket coudn't creat\n");
	exit(0);
	}
	/*
	network_socket: socket descriptor, an integer (like a file-handle)
	domain: integer, communication domain e.g., AF_INET (IPv4 protocol) , AF_INET6 (IPv6 protocol)
	type: communication type
	SOCK_STREAM: TCP(reliable, connection oriented)
	SOCK_DGRAM: UDP(unreliable, connectionless)
	protocol: Protocol value for Internet Protocol(IP), which is 0. This is the same number which 		appears on protocol field in the IP header of a packet.(man protocols for more details)
	*/
	
	//socket  created..
	
/*now specify an address structure for socket*/
struct sockaddr_in server_address; // server address
server_address.sin_family=AF_INET;
server_address.sin_port = htons(PORT); //htons chage port to n/w byte as per endiness
server_address.sin_addr.s_addr=INADDR_ANY;//server address here 0.0.0.0

// now connect the socket
int connect_state=connect(network_socket,(struct sockadd *) &server_address,sizeof(server_address));
if(connect_state<0){
printf("There was an error makin a connection\n");
exit(0);
}
//recieve data from the server 
char server_response[256];
recv(network_socket,&server_response,sizeof(server_response),0);

//after response print what data recieve
printf("The server send the data: %s\n",server_response);

//close the socket

close(network_socket);
return 0;
}
