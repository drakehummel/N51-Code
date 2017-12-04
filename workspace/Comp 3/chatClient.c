#include "chatClient.h"

void *recvFunc(void *serverFd);


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


	pthread_t socketThreadID;



/////SETTING UP THE SOCKET//////

	if(argc != 3)
	{
		printf("Please enter a valid IP, and a valid Port between 1025 and 65,535\n");
		return 0;
	}

	serverFd = socket(AF_INET, SOCK_STREAM, 0);					//parameters- ipv4, tcp, default
	if(serverFd == -1)
	{
		perror("Socket Error");
		exit(EXIT_FAILURE);
	}

/////CALLING PORT VALIDATOR//////

	if (inputValInt(port) == -1)
	{
		perror("Invalid Port");
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

	pthread_create(&socketThreadID, NULL, &recvFunc, (void *)&serverFd);

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

	}
}

void *recvFunc(void *serverFd)
{
	int sFd = *((int *)serverFd);
	int bytesRec = 0;
	char* recvBuf = NULL;

	while(1)
	{
		recvBuf = calloc(sizeof(char), MAXBUF);
		if((bytesRec = recv(sFd, recvBuf, MAXBUF, 0)) <= 0)
		{
			break;
		}

		printf("%s\n", recvBuf);
		printf("%d\n", bytesRec);
		free(recvBuf);
		recvBuf = NULL;
	}

	close(serverFd);
	return(EXIT_SUCCESS);
}
