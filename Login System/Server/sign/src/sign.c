#include "sign.h"

void sign_in(int csockfd, struct __mysql *mysql, struct sockaddr_in addr){

	struct sign_in_credentials cred;
	unsigned int len=sizeof(struct sign_in_credentials);

	if(recv(csockfd, (char*)&cred, len, 0)==-1){

		w_connection_log(strerror(errno), inet_ntoa(addr.sin_addr), "Connection problem with", LOG_SRV_C, 3);
	
	}else{

		w_connection_log("Successful", inet_ntoa(addr.sin_addr), "Reiceving login credentials from", LOG_SRV_C, 3);

		hash_pass(cred.password);

		int userID=check_data(mysql, cred);

		if(send(csockfd, (const char*)&userID, sizeof(unsigned int), 0)==-1){

			w_connection_log(strerror(errno), inet_ntoa(addr.sin_addr), "Connection problem with", LOG_SRV_C, 3);

		}else{

			w_connection_log("Successful", inet_ntoa(addr.sin_addr), "Sending userID to", LOG_SRV_C, 3);
		}
	}

	mysql_free_result(mysql->res);
}

void sign_up(int csockfd, struct __mysql *mysql, struct sockaddr_in addr){

	struct sign_up_credentials cred;

	if(recv(csockfd, (char*)&cred, sizeof(struct sign_up_credentials), 0)==-1){

		w_connection_log(strerror(errno), inet_ntoa(addr.sin_addr), "Connection problem with", LOG_SRV_C, 3);
	
	}else{

		w_connection_log("Successful", inet_ntoa(addr.sin_addr), "Receiving new account credentials from", LOG_SRV_C, 3);

		short int response=verify_username(cred.username, mysql);

		if(response==0){

			hash_pass(cred.password);

			response=insert_data(&mysql->mysql, cred);
		}

		if(send(csockfd, (const char*)&response, sizeof(short int), 0)==-1){

			w_connection_log(strerror(errno), inet_ntoa(addr.sin_addr), "Connection problem with", LOG_SRV_C, 3);
		
		}else{

			w_connection_log("Successful", inet_ntoa(addr.sin_addr), "Sending response to", LOG_SRV_C, 3);
		}
	}
}

void hash_pass(char *password){

	size_t len, password_len=strlen(password);

	char *salt;

	w_log("...", "Hashing password", LOG_SRV, 0);

	if(password_len<=9){
	
		salt=(char*)malloc(strlen(SALT5)*sizeof(char)+1);

		strncat(salt, SALT5, strlen(SALT5)+1);

	}else if(password_len<=15){

		salt=(char*)malloc(strlen(SALT4)*sizeof(char)+1);

		strncat(salt, SALT4, strlen(SALT4)+1);

	}else if(password_len<=20){

		salt=(char*)malloc(strlen(SALT3)*sizeof(char)+1);

		strncat(salt, SALT3, strlen(SALT3)+1);

	}else if(password_len<=25){

		salt=(char*)malloc(strlen(SALT2)*sizeof(char)+1);

		strncat(salt, SALT2, strlen(SALT2)+1);
	
	}else if(password_len<=30){

		salt=(char*)malloc(strlen(SALT1)*sizeof(char)+1);
	
		strncat(salt, SALT1, strlen(SALT1)+1);

	}else{

		salt=(char*)malloc(strlen(SALT0)*sizeof(char)+1);

		strncat(salt, SALT0, strlen(SALT0)+1);
	}

	len=snprintf(NULL, 0, salt, password_len, password);

	char *pass=(char*)malloc(len*sizeof(char)+1);

	snprintf(pass, len+1, salt, strlen(password), password);

	unsigned char digest[SHA512_DIGEST_LENGTH];

	SHA512((unsigned char*)pass, strlen(pass), digest);

	memset(password, 0, strlen(password)+1);

	for(unsigned int i=0; i<SHA512_DIGEST_LENGTH; i++){

		snprintf(&password[i*2], 5, "%02x", (unsigned int)digest[i]);
	}

	free(pass);
}

short int verify_username(const char *username, struct __mysql *mysql){

	char query[60];

	snprintf(query, 60, "select userID from users where username='%s';", username);

	short int rv;

	if(mysql_query(&mysql->mysql, query)!=0){

		w_log(mysql_error(&mysql->mysql), "ERROR", LOG_DB, 2);

		rv=-1;
	
	}else{

		w_log("Successful", "verifying username", LOG_SRV, 0);

		mysql->res=mysql_store_result(&mysql->mysql);

		mysql->row=mysql_fetch_row(mysql->res);

		if(mysql->row==NULL){

			rv=0;

		}else{

			rv=-2;
		}
	}

	mysql_free_result(mysql->res);

	return rv;
}

short int insert_data(MYSQL *mysql, struct sign_up_credentials cred){

	char str_format[]="insert into users values(DEFAULT, '%s', '%s', '%s', '%c', '%d-%d-%d');";

	size_t len=snprintf(NULL, 0, str_format, cred.name, cred.username, cred.password, 
		cred.genre, cred.birth.year, cred.birth.month, cred.birth.day);

	char *query=(char*)malloc(len*sizeof(char)+1);

	snprintf(query, len+1, str_format, cred.name, cred.username, 
		cred.password, cred.genre);

	short int rv;

	if(mysql_query(mysql, query)!=0){

		w_log(mysql_error(mysql), "ERROR", LOG_DB, 2);

		rv=-1;
	
	}else{

		w_log("Successful", "Inserting data", LOG_DB, 0);

		rv=0;
	}

	free(query);

	query=NULL;

	return rv;
}

int check_data(struct __mysql *mysql, struct sign_in_credentials cred){

	char str_format[]="select userID from users where username='%s' and password='%s';";

	size_t len=snprintf(NULL, 0, str_format, cred.username, cred.password);

	char *query=(char*)malloc(len*sizeof(char)+1);

	snprintf(query, len+1, str_format, cred.username, cred.password);

	int rv;

	if(mysql_query(&mysql->mysql, query)!=0){

		w_log(mysql_error(&mysql->mysql), "ERROR", LOG_DB, 2);
		
		rv=-1;

	}else{

		w_log("Successful", "Checking data", LOG_DB, 0);

		mysql->res=mysql_store_result(&mysql->mysql);

		mysql->row=mysql_fetch_row(mysql->res);

		if(mysql->row==NULL){

			rv=-2;
		
		}else{

			rv=atoi(mysql->row[0]);
		}
	}

	free(query);

	query=NULL;

	return rv;
}