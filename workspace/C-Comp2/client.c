/*
 * client.c
 *
 *  Created on: Apr 30, 2017
 *      Author: root
 */


#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]){
	int clientSocket;
	char buffer[1024];
	struct sockaddr_in serverAddr;

		//Creating the socket
	socklen_t addr_size;
		//Arguments- Internet domain, Stream socket, Default protocol (TCP)
	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
		//Setting all padding bits to 0
	memset(&serverAddr, '\0', sizeof serverAddr);
		//Zeroing out the buffer
 	memset(buffer, 0, 1024);

		// Server Address Family = Internet
	serverAddr.sin_family = AF_INET;
 		//Setting port number (htons gives proper byte order)
	serverAddr.sin_port = htons(*(short *)argv[1]);
		//Setting IP Address
	if(inet_pton(AF_INET, argv[2], &(serverAddr.sin_addr)) <= 0) {
		printf("error!\n");
		return 0;
	}

	printf("Port = %s, IP Address = %s\n", argv[1], argv[2]);
		//Setting all padding bits to 0


		//Connect the socket to the server using the address struct
	if(connect(clientSocket, (struct sockaddr *) &serverAddr, sizeof serverAddr) != 0)
	{
		printf("\nNo Connection\n\n");
		return(0);
	}

	printf("\nServer Connected\n\n");

		//Get user input
	printf("Please enter the message you would like the server to echo back.\n");
	fgets(buffer, 100, stdin);

		//Send message
	send(clientSocket, buffer, strlen(buffer), 0);

		//Read the message from the server into the buffer
	recv(clientSocket, buffer, strlen(buffer), 0);


	printf("\nData received: %s\n",buffer);
	close(clientSocket);

	return 0;
}


