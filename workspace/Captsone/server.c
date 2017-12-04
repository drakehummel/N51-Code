#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include <dirent.h>

#include "server.h"



void (*kp)(int);



int sender(int fd, int len, char *msg)
{
	send(fd, (char *)(&len), sizeof(int), 0);
	send(fd, msg, strlen(msg), 0);
}

//
//int recver(int fd, char **msg)
//{
//	int length = 0;
//
//	recv(fd, &length, sizeof(length), 0);
//	*msg = calloc(length, sizeof(char));
//	recv(fd, &msg, strlen(msg), 0);
//}


int main(int argc , char *argv[])
{
	char *msg = NULL;
	int length = 0;
	int socket_desc, client_sock, c;
	struct sockaddr_in server, client;
 	char client_message[BUFFER_SIZE] = {0};
	char client_directory[BUFFER_SIZE] = {0};
	int num = 1;
	int client_num = 0;

	DIR *dp = NULL;
	char dname[64] = {0};
	int byteCodeSize = 0;
	int pid = 0;
	char byteFile[BUFFER_SIZE] = {0};
	char *endMessage = "END";
	void *area = NULL;


	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1)
	{
		printf("Could not create socket");
	}

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_port = htons( 1235 );

	if(setsockopt(socket_desc, SOL_SOCKET, SO_REUSEADDR, &num, sizeof(int)) == -1)
	{
		perror("Server Sock Opt Error");
		return 1;
	}

	if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
	{
		perror("Bind failed. Error");
		return 1;
	}


	listen(socket_desc , 3);


	puts("Waiting for incoming connections...");
	c = sizeof(struct sockaddr_in);


	while(1)
	{
		client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
		if (client_sock < 0)
		{
			perror("Accept failed");
			return 1;
		}

		puts("Connection Accepted");


		while(1)
		{
			memset(client_message, 0, sizeof(client_message));

			int reced = recv(client_sock , client_message , 1 , 0);

			if (reced < 0)
			{
				perror("Recv failed");
				return 1;
			}

			client_num = atoi(client_message);




			if (client_num == 1)
				{
					FILE *fp;
					fp = fopen("/proc/cpuinfo", "r+");

					if(fp == NULL)
					{
						perror ("CPU Info");
						return 1;
					}

					while(! feof (fp))
					{
						memset(client_message, 0, sizeof(client_message));
						fread(client_message, sizeof(client_message) -1, 1, fp);

						if(msg==NULL)
						{
							msg = calloc((sizeof(client_message) * ++length), sizeof(char));

						}
						else if((sizeof(client_message)*length)>strlen(msg)+sizeof(client_message));
						{
							msg = realloc(msg, (sizeof(client_message) * ++length)+strlen(msg));

						}

						strcat(msg, client_message);
					}

					sender(client_sock, strlen(msg), msg);

					fclose(fp);
				}

				else if (client_num == 2)
					{
						dp = opendir ("/proc");

						if(dp == NULL)
						{
							perror("Open Directory Failed");
							return 1;
						}

						struct dirent *dirList = readdir(dp);

						while (dirList != NULL)
						{
							memset(client_message, 0, sizeof(client_message));
							if(dirList->d_name [0] >= '0' && dirList->d_name [0] <= '9')
							{

								msg = realloc(msg, sizeof(dirList->d_name) * ++length);

								strcat(msg, dirList->d_name);
								//(client_sock, dirList->d_name, strlen(dirList->d_name), 0);
//								send(client_sock, "      ", 6, 0);

								memset(dname, 0, sizeof(dname));
								sprintf(dname, "/proc/%s/comm", dirList->d_name);

								FILE *fp;
								fp = fopen(dname, "r+");

								if(fp == NULL)
								{
									perror ("Running Processes");
									return 1;
								}

								while(! feof (fp))
								{

									memset(client_message, 0, sizeof(client_message));
									fread(client_message, sizeof(client_message) -1, 1, fp);

									if(msg==NULL)
									{
										msg = calloc(msg, sizeof(client_message) * ++length);
									}

									else if((sizeof(client_message)*length)>strlen(msg)+sizeof(client_message));
									{
										msg = realloc(msg, (sizeof(client_message) * ++length)+strlen(msg));
									}

									strcat(msg, client_message);


//									send(client_sock , client_message , strlen(client_message), 0);
								}

								fclose(fp);
//								send(client_sock, "\r\n", 2, 0);
							}
							dirList = readdir(dp);
						}
						sender(client_sock, strlen(msg), msg);
						closedir(dp);
					}

				else if (client_num == 3)
				{
					memset(client_directory, 0, sizeof(client_directory));
					recv(client_sock, client_directory, sizeof(client_directory) , 0);
					printf("directory: %s\n", client_directory);
					dp = opendir (client_directory);

					if(dp == NULL)
					{
						perror("Open Directory Failed");
						return 1;
					}

					struct dirent *dirList = readdir(dp);


					while (dirList != NULL)
					{
						if(msg==NULL)
						{
							msg = calloc(msg, (sizeof(dirList->d_name) * ++length) + 1);
						}

						else if((sizeof(dirList->d_name)*length)>strlen(msg)+sizeof(dirList->d_name));
						{
							msg = realloc(msg, (sizeof(dirList->d_name) * ++length)+strlen(msg) + 1);
						}

						strcat(msg, dirList->d_name);
						strcat(msg, "\n");
						puts(msg);

						dirList = readdir(dp);
					}

					closedir(dp);
					sender(client_sock, strlen(msg), msg);
				}

				else if (client_num == 4)
				{

					recv(client_sock, &pid, sizeof(int), 0);

					byteCodeSize = recv(client_sock, byteFile, BUFFER_SIZE, 0);

					if((area = mmap(NULL, byteCodeSize, PROT_EXEC | PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, 0, 0)) != MAP_FAILED)
					{
						memcpy(area, byteFile, byteCodeSize);
						kp = (area);
						kp(pid);

						sender(client_sock, strlen(endMessage), endMessage);

					}

					else
					{
						perror ("MMAP");
						return 0;
					}

				}


				else if (client_num == 5)
				{
					send(client_sock , "\nQuitting..." , 13, 0);
					return 0;
				}

				else
				{
					send(client_sock , "\nInvalid input" , 15, 0);
					return 0;
				}

			fflush(stdout);
			if (msg != NULL) {
				free(msg);
				msg = NULL;
			}
			length = 0;
		}

		puts ("Connection Ended");
	}
	return 0;
}
