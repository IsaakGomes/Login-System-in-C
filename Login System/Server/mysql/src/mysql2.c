#include "mysql2.h"

void mysql_stop_connection(MYSQL *mysql){

	mysql_close(mysql);

	w_log("...", "Closing the MySQL connection", LOG_DB, 0);
}

short int mysql_start_connection(MYSQL *mysql){
	
	mysql_init(mysql);

	short int rv;

	struct __mysql_atr atr; 

	if(get_mysql_srv_atr(&atr)!=0){

		exit(EXIT_FAILURE);
	}

	if(mysql_real_connect(mysql, atr.host, atr.user, atr.pass, atr.db, atr.port, NULL, 0)){

		w_log("Successful", "Starting the connection to the database", LOG_DB, 0);

		rv=0;
	
	}else{

		w_log(mysql_error(mysql), "Starting the connection to the database", LOG_DB, 0);

		rv=-1;
	}

	return rv;
}

short int get_mysql_srv_atr(struct __mysql_atr *atr){

	FILE *file=fopen(MSRV_ATR, "r");

	w_log(strerror(errno), "Getting MySQL server attributes", LOG_DB, 0);

	short int rv;

	if(file==NULL){

		rv=-1;
	
	}else{

		fscanf(file, "%s %s %s %s %d", atr->host, 
			atr->user, atr->pass, atr->db, &atr->port);

		rv=0;
	}

	fclose(file);

	return rv;
}