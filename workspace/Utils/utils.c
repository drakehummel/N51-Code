
#include "utils.h"


////////GETTING INPUT AND REALLOCING////////


void inputVal(char** wholeMessage, int size)
{
	char* message = calloc(sizeof(char), size);
	int readSize = size;
	char* tempBuf = NULL;
	int count = 0;

	printf("Connection Established. Please enter the message you would like to send the other clients.\n");

	do
	{
		memset(message, 0, readSize);

		if (fgets(message, readSize, stdin) == -1)
		{
			perror("fgets");
			free(message);
			exit(EXIT_FAILURE);
		}

		if (strchr(&message, '\n') == NULL)
		{
			size += readSize;
			tempBuf = realloc(*wholeMessage, size);					//only returning a pointer for a potential error

			if(tempBuf == NULL)
			{
				free(*wholeMessage);
				*wholeMessage = NULL;
				free(message);
				perror("realloc");
				exit(EXIT_FAILURE);
			}

			else
			{
				*wholeMessage = tempBuf;							//this assigns the reallocation to wholeMessage
				//&tempBuf = NULL;
			}

		}

		memset(*wholeMessage + count, 0, readSize);
		count += readSize;
		strncat(*wholeMessage, message, size);						//concatenating message to the end of wholeMessage

	}while ((*wholeMessage)[strlen(*wholeMessage) - 1] != '\n');	//all while the new wholeMessage's last character isnt a newline

	free(message);
	message = NULL;

	return ;
}


/////////PORT VALIDATION/////////


int inputValInt(char* port)
{

	int intPort = 0;
	char *badChar = NULL;


	intPort = strtol(port, &badChar, 10);

	if(*badChar != '\n' && *badChar != '\0')														//Checking for newline or null-term because that would be a valid non-integer, otherwise its invalid
	{
		printf("Please enter a valid IP, and a valid Port between 1025 and 65,535\n\n");
		return -1;
	}

	if (intPort >= MIN_PORT)
		{
			return 1;
		}

		else if (intPort <= MAX_PORT)
		{
			return 1;
		}

		else
		{
			return -1;
		}

	return 1;
}




char* recvRealloc(int clientFd)
{

	int bytesRec = 0;
	int size = 100;
	char* buf = calloc(sizeof(char), size);
	char* wholeBuf = calloc(sizeof(char), size);
	char* tempBuf = NULL;
	int readSize = size;


	FILE* messageLog = fopen("messageLog.txt", "a");

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
			exit(EXIT_FAILURE);
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

return wholeBuf;
}
