#ifndef SERVER_H
#define SERVER_H

#include "logs.h" //Func. w_log
#include "sign.h" //Func. sign_in() and sign_up(); 

#include <errno.h> //mac. errno
#include <stdio.h> //fun. printf()
#include <stdlib.h> //func. exit()
#include <string.h> //func. strncat

#include <unistd.h> //func. close()
#include <sys/types.h> //socklen_t
#include <arpa/inet.h> //func. inet_addr(), func. htons()
#include <netinet/in.h> //struc. sockaddr_in
#include <sys/socket.h> //struct. sockaddr, macros, func. socket(), func. bind() ...

#define SRV_ATR "server/server_attributes"

#define MAX_CONNECTIONS 10

struct server_atr{
	
	unsigned int port;
	char host[40];
};

enum request{SIGN_IN, SIGN_UP, _ERROR_};

extern void start_server(void);
extern void wait_for_connections(int sockfd);
extern short int get_server_atr(struct server_atr *atr);

#endif //SERVER_H