#ifndef SIGN_H
#define SIGN_H

#include "logs.h" //WriteLog(), WriteConnectionLog()...
#include "mysql.h" //For func. mysql_query(), mysql_store_result()...
#include "mysql2.h" //for struct __mysql

#include <stdio.h> //for func.snprintf();
#include <stdlib.h> //for func.atoi(), func.malloc();
#include <string.h> //for func.strlen()
#include <stdio_ext.h> //for func. fpurge();

#include <openssl/sha.h> //for fun.SHA256()

#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define SALT0 "&*(%ld)->(%s)->||<-F16!=F22=PCTO+=00;"
#define SALT1 "srvstk#$_%ld=[|%s|]4AB4Lpkx=P90FN=Kp;"
#define SALT2 "fHg47*(%ld=f12ff=)?=[|%s|]!=!KY>L=Ky;"
#define SALT3 "gTRYLK||=(8=|%ld|=fgvt0X)?=[|%s|]=Kt;"
#define SALT4 "{Fyth(Ak%$#)([%ld%])=([%s])AR-15}=Ko;"
#define SALT5 "ppk-150-lgDFA=(U)f20lehfCc=%ld=%s=Kl;" 

struct sign_in_credentials{

	char username[16], password[129];
};

struct sign_up_credentials{

	char name[256];
	char username[16], password[129];

	enum __genre{MALE=77, FEMALE=70, OTHER=79}genre; //77='M'...70='F'...79='O'

	struct date_of_birth{unsigned short int year, month, day}birth;
};

extern void sign_in(int csockfd, struct __mysql *mysql, struct sockaddr_in addr);
extern void sign_up(int csockfd, struct __mysql *mysql, struct sockaddr_in addr);

extern void hash_pass(char *password);
extern short int verify_username(const char *username, struct __mysql *mysql);
extern short int insert_data(MYSQL *mysql, struct sign_up_credentials cred);

extern int check_data(struct __mysql *mysql, struct sign_in_credentials cred);

#endif //SIGN_H