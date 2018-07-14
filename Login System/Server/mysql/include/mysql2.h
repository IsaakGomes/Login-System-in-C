#ifndef MYSQL2_H
#define MYSQL2_H

#include "logs.h" 
#include "mysql.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MSRV_ATR "server/mysql_server_attributes"

struct __mysql_atr{

	char host[40], user[16], pass[101], db[31];
	unsigned int port;
};

struct __mysql{
	
	MYSQL mysql;
	MYSQL_ROW row;
	MYSQL_RES *res;
};

extern void mysql_stop_connection(MYSQL *mysql);
extern short int mysql_start_connection(MYSQL *mysql);
extern short int get_mysql_srv_atr(struct __mysql_atr *atr);

#endif //MYSQL2_H