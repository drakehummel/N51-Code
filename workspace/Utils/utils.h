
#ifndef UTILS_H_
#define UTILS_H_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1000000
#define MIN_PORT 1025
#define MAX_PORT 65535

void inputVal(char** wholeMessage, int size);
int inputValInt(char* port);
char* recvRealloc(int clientFd);


#endif /* UTILS_H_ */
