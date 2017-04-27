#pragma once


#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/wait.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>
#include <string>
const int MAXBUFLEN=100;
const int MYPORT=5000;
const int BACKLOG=10;
class Socket
{
public:
	Socket();
	~Socket();
	void initial();
	int mysend(std::string);
	std::string myreceive();
private:
	int sockfd;
	int new_fd;
	struct sockaddr_in my_addr; /* my address information */
	struct sockaddr_in their_addr; /* connector's address information */
	socklen_t sin_size;
	int initialstate;
};

