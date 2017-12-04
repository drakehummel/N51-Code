#ifndef COMP4_H_
#define COMP4_H_

#define MAXBUF 65536

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>

#include<netinet/ip_icmp.h>
#include<netinet/udp.h>
#include<netinet/tcp.h>
#include<netinet/ip.h>
#include<netinet/if_ether.h>
#include<net/ethernet.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<signal.h>
#include <sys/mman.h>

#define handle_error(msg)\
do { perror(msg); exit(EXIT_FAILURE); } while (0)

int tcp = 0,udp = 0, icmp = 0,others = 0,total = 0;
struct sockaddr_in source,dest;

void handler(int sig, siginfo_t *si, void *sock_raw);
void sniffer(unsigned char* buffer, int size);


#endif
