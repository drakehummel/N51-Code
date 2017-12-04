//#include <string.h>
//#include <stdio.h>
//#include <stdlib.h>
//
//
//
//////////GETTING INPUT AND REALLOCING////////
//
//
//void inputVal(char** wholeMessage, int size)
//{
//	char* message = calloc(sizeof(char), size);
//	int readSize = size;
//	char* tempBuf = NULL;
//	int count = 0;
//
//	printf("Please enter the message you would like to have the server echo back.\n");
//
//
//
//	do
//	{
//		memset(message, 0, readSize);
//		//getting input and assigning it to message
//		if (fgets(message, readSize, stdin) == -1)
//		{
//			perror("fgets");
//			free(message);
//			exit(EXIT_FAILURE);
//		}
//		if (strchr(&message, '\n') == NULL)
//		{
//			size += readSize;
//			tempBuf = realloc(*wholeMessage, size);		//only returning a pointer for a potential error
//
//			if(tempBuf == NULL)
//			{
//				free(*wholeMessage);
//				*wholeMessage = NULL;
//				free(message);
//				perror("realloc");
//				exit(EXIT_FAILURE);
//			}
//
//			else
//			{
//				*wholeMessage = tempBuf;				//this assigns the reallocation to wholeMessage
//				//&tempBuf = NULL;
//			}
//
//		}
//
//		memset(*wholeMessage + count, 0, readSize);
//		count += readSize;
//		strncat(*wholeMessage, message, size);			//concatenating message to the end of wholeMessage
//
//	}while ((*wholeMessage)[strlen(*wholeMessage) - 1] != '\n');	//all while the new wholeMessage's last character isnt a newline
//
//	free(message);
//	message = NULL;
//
//	return;
//}
//
//
//
///////////PORT VALIDATION/////////
//
//
//#define MIN_PORT 1025
//#define MAX_PORT 65535
//
//
//int inputValInt(char* port)
//{
//
//	int i = 0;
//	int intPort;
//
//
//		while (port [i] != '\n')
//		{
//			if (! isdigit(port [i]))
//			{
//				return -1;
//			}
//
//		i++;
//		}
//
//	intPort = (int)port;
//
//	if (intPort >= MIN_PORT)
//	{
//		return 1;
//	}
//
//	else if (intPort <= MAX_PORT)
//	{
//		return 1;
//	}
//
//	else
//	{
//		return -1;
//	}
//
//}
//
//
//
