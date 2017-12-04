#ifndef CHATSERVER_H_
#define CHATSERVER_H_

#define NUMENTRIES 10


#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/queue.h>
#include <fcntl.h>

#include "utils.h"
pthread_mutex_t lock;

void* chatter(void *clientFd);



LIST_HEAD(listHead, listEntry) head = LIST_HEAD_INITIALIZER(head);		//creates a structure called listHead that is the head of the linked list

struct listEntry
{
	LIST_ENTRY(listEntry) entryObject;									//pointer to next element
	int fd;																//this is going to store the file descriptor of who is connecting
};






#endif
