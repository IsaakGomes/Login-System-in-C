#include "server.h"

void start_server(void){

	w_log("...", "Starting the server", LOG_SRV, 0);

	struct server_atr atr;

	struct sockaddr_in addr;

	int sockfd=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if(sockfd==-1){

		w_log(strerror(errno), "Creating socket", LOG_SRV, 0);
	
	}else{

		w_log("Successful", "Creating socket", LOG_SRV, 0);
	}

	if(get_server_atr(&atr)!=0){

		close(sockfd);
		exit(EXIT_FAILURE);
	}

	addr.sin_family=AF_INET;
	addr.sin_port=htons(atr.port);
	addr.sin_addr.s_addr=inet_addr(atr.host);

	socklen_t addr_len=sizeof(addr);

	if(bind(sockfd, (struct sockaddr*)&addr, addr_len) !=0){

		w_log(strerror(errno), "Binding error", LOG_SRV, 0);

		exit(EXIT_FAILURE);
	
	}else{

		w_log("Successful", "Binding", LOG_SRV, 0);
	}

	wait_for_connections(sockfd);
}

void wait_for_connections(int sockfd){

	struct __mysql mysql;

	if(mysql_start_connection(&mysql.mysql)!=0){

		mysql_stop_connection(&mysql.mysql);

		exit(EXIT_FAILURE);
	}

	if(listen(sockfd, MAX_CONNECTIONS)!=0){

		w_log(strerror(errno), "Listening error", LOG_SRV, 0);
	
		exit(EXIT_FAILURE);
	
	}else{

		w_log("Succesful", "Starting the server", LOG_SRV, 0);
		w_log("...", "Listening", LOG_SRV, 1);
	}

	int csockfd;
	struct sockaddr_in addr;

	socklen_t len=sizeof(addr);

	enum request rq;

	short int cont=0;

	while(1){

		if(cont!=0){

			w_log("...", "Waiting for new connections", LOG_SRV_C, 2);
		}

		csockfd=accept(sockfd, (struct sockaddr*)&addr, &len);

		if(csockfd==-1){

			w_connection_log(strerror(errno), inet_ntoa(addr.sin_addr), "Connection problem with", LOG_SRV_C, 3);

		}else{

			w_connection_log("Successful", inet_ntoa(addr.sin_addr), "Connection accepted from", LOG_SRV_C, 3);

			if(recv(csockfd, (char*)&rq, sizeof(enum request), 0)==-1){

				rq=_ERROR_;
			}

			if(rq==SIGN_IN){

				w_connection_log("...", inet_ntoa(addr.sin_addr), "Sign in request from", LOG_SRV_C, 3);

				sign_in(csockfd, &mysql, addr);
				
			}else if(rq==SIGN_UP){

				w_connection_log("...", inet_ntoa(addr.sin_addr), "Sing up request from", LOG_SRV_C, 3);

				sign_up(csockfd, &mysql, addr);
			
			}else{

				w_connection_log(strerror(errno), inet_ntoa(addr.sin_addr), "Connection problem with", LOG_SRV_C, 3);
			}
		}

		cont=1;
	}

	close(sockfd);
	close(csockfd);
}

short int get_server_atr(struct server_atr *atr){
	
	FILE *file=fopen(SRV_ATR, "r");

	short int rv;

	if(file==NULL){

		w_log(strerror(errno), "Getting server attributes", LOG_SRV, 0);

		rv=-1;

	}else{

		w_log("Successful", "Getting server attributes", LOG_SRV, 0);

		fscanf(file, "%s %d", atr->host, &atr->port);

		rv=0;
	}

	fclose(file);

	return rv;	
}