#include "Comp4.h"

int main()
{
	int saddr_size , data_size;
	struct sockaddr saddr;
	unsigned short iphdrlen = 0;
	unsigned char *buffer = (unsigned char *) malloc(MAXBUF);
	struct iphdr *iph = (struct iphdr *)( buffer  + sizeof(struct ethhdr));
	iphdrlen = iph->ihl*4;
	struct tcphdr *tcph=(struct tcphdr*)(buffer + iphdrlen + sizeof(struct ethhdr));

	struct sigaction sa;

	int sock_raw = socket( AF_PACKET , SOCK_RAW , htons(ETH_P_ALL));

	if(sock_raw < 0)
	{
		perror("Socket Error");
		return 1;
	}

	sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = handler;
    if (sigaction(SIGINT, &sa, NULL) == -1)
   	handle_error("Signal Action");

	printf("Network Sniffer Started\n");


	while(1)
	{
		saddr_size = sizeof(saddr);
		data_size = recvfrom(sock_raw , buffer , MAXBUF , 0 , &saddr , (socklen_t*)&saddr_size);

		if(data_size < 0)
		{
			printf("Recvfrom error , failed to get packets\n");
			return 1;
		}

		sniffer(buffer, data_size);

		memset(&source, 0, sizeof(source));
			source.sin_addr.s_addr = iph->saddr;

		memset(&dest, 0, sizeof(dest));
		dest.sin_addr.s_addr = iph->daddr;

		printf("\n\n\n____________________________________\n");
		printf("Source IP        : %s\n",inet_ntoa(source.sin_addr));
		printf("Destination IP   : %s\n",inet_ntoa(dest.sin_addr));
	   	printf("Source Port      : %u\n",ntohs(tcph->source));
	   	printf("Destination Port : %u\n\n",ntohs(tcph->dest));

		printf("TCP    : %d\n"
				"UDP    : %d\n"
				"ICMP   : %d\n"
				"Others : %d\n"
				"Total  : %d\n", tcp, udp, icmp, others, total);
	}

	return 0;
}


/*
@brief This function increments the number of each type of packet that it sees.
@param buffer This is the data recv'd from the socket
@param size This is the size of the data recv'd
 */
void sniffer(unsigned char* buffer, int size)
{
	struct iphdr *iph = (struct iphdr*)(buffer + sizeof(struct ethhdr));
	++total;

	switch (iph->protocol)
	{
		case IPPROTO_ICMP:
			++icmp;
			break;

		case IPPROTO_TCP:
			++tcp;
			break;

		case IPPROTO_UDP:
			++udp;
			break;

		default:
			++others;
			break;
	}
}

/*
@brief This function captures the Ctrl+C and gracefully closes the socket
@param sig This is the signal that I'm handling
@param si This is info about the signal recv'd
@param sock_raw This is the socket
 */
void handler(int sig, siginfo_t *si, void *sock_raw)
{
	printf("\nCaptured Ctrl+C\n");
	close(*((int *)sock_raw));
	printf("Finished\n");
	exit(EXIT_SUCCESS);

}

