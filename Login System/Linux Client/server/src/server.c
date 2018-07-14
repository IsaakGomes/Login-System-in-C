#include "server.h"

int start_connection(void){

	struct server_atr atr;

	struct sockaddr_in addr;

	int sockfd=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	get_server_atr(&atr);

	addr.sin_family=AF_INET;
	addr.sin_port=htons(atr.port);
	addr.sin_addr.s_addr=inet_addr(atr.host);

	socklen_t len=sizeof(addr);

	if(connect(sockfd, (struct sockaddr*)&addr, len)!=0){

		sockfd=-1;
	}

	return sockfd;
}

void get_server_atr(struct server_atr *atr){
	
	FILE *file=fopen(SRV_ATR, "r");

	if(file==NULL){

		exit(EXIT_FAILURE);

	}else{

		fscanf(file, "%s %d", atr->host, &atr->port);
	}

	fclose(file);	
}