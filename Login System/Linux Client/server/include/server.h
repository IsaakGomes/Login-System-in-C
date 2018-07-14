#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define SRV_ATR "server/server_attributes"

struct server_atr{
	
	unsigned int port;
	char host[40];
};

extern int start_connection(void);
extern void get_server_atr(struct server_atr *atr);

#endif //SERVER_H