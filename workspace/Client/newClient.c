#include "newClient.h"


int main(int argc, char *argv[])
{
	char* ip = argv[1];
	char* port = argv[2];
	int serverFd = 0;
	struct sockaddr_in addr = {0};
	socklen_t addrLen = sizeof(addr);
	struct in_addr ipAddr = {0};
	char *badChar = NULL;

	char* wholeMessage = NULL;
	int messageSize = 0;
	int bufSize = 100;



/////SETTING UP THE SOCKET//////

	if(argc != 3)
	{
		printf("Please enter a valid IP, and a valid Port between 1025 and 65,535\n");
		return 0;
	}

	serverFd = socket(AF_INET, SOCK_STREAM, 0);					//parameters- ipv4, tcp, default
	if(serverFd == -1)
	{
		perror("Socket Errro");
		exit(EXIT_FAILURE);
	}

/////CALLING PORT VALIDATOR//////

	if (inputValInt(port) == -1)
	{
		perror("Invlaid Port");
		exit(EXIT_FAILURE);
	}

	addr.sin_family = AF_INET;
	addr.sin_port = htons(strtol(port, &badChar, 10));

	if(inet_pton(AF_INET, ip, &ipAddr) != 1)
	{
		perror("Invalid IP Address");
		exit(EXIT_FAILURE);
	}

	addr.sin_addr = ipAddr;
	if(connect(serverFd, (struct sockaddr *)(&addr), addrLen) == -1)
	{
		perror("Client Connect Error");
		exit(EXIT_FAILURE);
	}

//////COMMS START HERE//////

	while(1)
	{

/////CALLING INPUT FUNC//////

		inputVal(&wholeMessage, bufSize);

		if (wholeMessage == NULL)
		{
			puts("Buffer set to NULL");
			exit(EXIT_FAILURE);
		}

		messageSize = strlen(wholeMessage);


/////SENDING TO SERVER//////

		if(send(serverFd, wholeMessage, messageSize + 1, 0) == -1)
		{
			perror("Client Send Error");
			exit(EXIT_FAILURE);
		}


		memset(wholeMessage, 0, messageSize);


/////RECEIVING FROM SERVER//////

		if(recv(serverFd, wholeMessage, messageSize, 0) == -1)
		{
			perror("Client Recv Error");
			exit(EXIT_FAILURE);
		}

		printf("%s\n", wholeMessage);
		printf("Message size: %d\n\n", messageSize);
		free(wholeMessage);
		wholeMessage = NULL;
	}



	close(serverFd);
}
