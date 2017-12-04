#include "chatServer.h"


int main(int argc, char *argv[])
{
	char* ip = argv[1];
	char* port = argv[2];
	int serverFd = 0;
	int clientFd = 0;
	struct sockaddr_in addr = {0};
	socklen_t addrLen = sizeof(struct sockaddr_in);
	struct in_addr ipAddr = {0};
	char *badChar = NULL;
	int num = 1;

	struct listEntry *entry = NULL, *curNode = NULL;
	pthread_t threadID[10];

	int i = 0;

	if(pthread_mutex_init(&lock, NULL) !=0)
	{
		perror("Mutex Error");
		exit(EXIT_FAILURE);
	}



//////SETTING UP THE LINKED LIST///////

	LIST_INIT(&head);															//initialize the list


	LIST_FOREACH(curNode, &head, entryObject)							//It traverses each object in the list, and then prints for each entry
	{
		printf("Next entry id is %d\n", curNode->fd);
	}


//////SETTING UP SOCKET//////

	serverFd = socket(AF_INET, SOCK_STREAM, 0);									//parameters- ipv4, tcp, default
	if(serverFd == -1)
	{
		perror("Socket Error");
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

	if(inet_pton(AF_INET, ip, &ipAddr) == -1)
	{
		perror("Invalid IP Address");
		exit(EXIT_FAILURE);
	}

	addr.sin_addr = ipAddr;


//////ALLOWS THE IP TO BE REUSED/////

	if(setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR, &num, sizeof(int)) == -1)
	{
		perror("Server Sock Opt Error");
		exit(EXIT_FAILURE);
	}


	if(bind(serverFd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
	{
		perror("Bind Error");
		exit(EXIT_FAILURE);
	}

	if(listen(serverFd, 10) == -1)
	{
		perror("listen Error");
		exit(EXIT_FAILURE);
	}

//////COMMS START HERE//////

	while(1)
	{

		clientFd = accept(serverFd, (struct sockaddr *)(&addr), &addrLen);
		if(clientFd == -1)
		{
			perror("Accept Error");
			exit(EXIT_FAILURE);
		}

		printf("Connection Established\n");

		entry = (struct listEntry *)calloc(1, sizeof(struct listEntry));		//making a calloc call, and casting the return (which is a void pointer) to a struct list entry pointer
		entry->fd = clientFd;													//making fd within my listEntry struct equal to clientFd (int)


		pthread_mutex_lock(&lock);
		LIST_INSERT_HEAD(&head, entry, entryObject);
		pthread_mutex_unlock(&lock);

		pthread_create(&threadID[i], NULL, &chatter, (void *)entry);						//creates a thread (a subprocess kind of) with these parameters (thread ID, attributes, a func, and a parameter)
		i++;

//		close(serverFd);
//		exit(EXIT_SUCCESS);
	}

}



///////FUNC FOR STARTING A THREAD AND REALLOCING//////

void *chatter(void *cFD)
{
	struct listEntry * entry = (struct listEntry*) cFD;			//casted cFD to a struct pointer from a void pointer and called it entry

	int bytesRec = 0;
	int size = 100;
	char* buf = calloc(sizeof(char), size);
	char* wholeBuf = calloc(sizeof(char), size);
	char* tempBuf = NULL;
	char* sendShit = NULL;
	int readSize = size;
	int clientFd = entry->fd;

	struct listEntry *curNode = {0};

	FILE* messageLog;



	while(1)
	{
		buf = calloc(sizeof(char), readSize);
		memset(wholeBuf, 0, size);

		do
		{
			bytesRec = recv(clientFd, buf, readSize, 0);

			if(bytesRec == 0)
			{
				break;
			}
			else if (bytesRec == -1)
			{
				perror("BytesRec Error");
				break;
			}

			if (strchr(buf, '\n') == NULL)
			{
				size += readSize;									//incrementing size by 100 each time
				printf("Size = %d\n", size);
				tempBuf = realloc(wholeBuf, size);					//reallocating the wholeMessage block of memory to the new size

				if(tempBuf == NULL)
				{
					free(wholeBuf);
					wholeBuf = NULL;
					free(buf);
					perror("Realloc Error");
					exit(EXIT_FAILURE);
				}

				else
				{
					wholeBuf = tempBuf;								//this assigns the reallocation to wholeMessage
					tempBuf = NULL;
				}

			}

				strncat(wholeBuf, buf, readSize);					//concatenating message to the end of wholeMessage

		}while ((wholeBuf)[strlen(wholeBuf) - 1] != '\n');		//all while the new wholeMessage's last character isnt a newline
		free(buf);
		sendShit = wholeBuf;

/////SENDING BACK TO CLIENTS///////

		if(bytesRec == 0)
		{
			break;
		}

		printf("%s\n", wholeBuf);
		free(wholeBuf);

		pthread_mutex_lock(&lock);
		messageLog=fopen("/tmp/messageLog.txt", "a+");
		fprintf(messageLog, "Client %d sent: %s\n", clientFd, sendShit);
		fclose(messageLog);
		pthread_mutex_unlock(&lock);

		pthread_mutex_lock(&lock);
		LIST_FOREACH(curNode, &head, entryObject)
		{
			if(curNode->fd != clientFd)
			{
				if(send(curNode->fd, sendShit, strlen(sendShit), 0) == -1)
				{
					perror("Send Error");
					exit(EXIT_FAILURE);
				}
			}
		}
		pthread_mutex_unlock(&lock);
	}

//////ENDING THE CONNECTION//////


	pthread_mutex_lock(&lock);

	LIST_REMOVE(entry, entryObject);						//Removes each entry
	printf("Removing entry %d\n", entry);
	free(entry);
	entry = NULL;

	pthread_mutex_unlock(&lock);

	close(clientFd);
}



