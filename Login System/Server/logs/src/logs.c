#include "logs.h"

void g_time(char *time_info){

	time_t timer;
	struct tm *local_time;

	time(&timer);
	local_time=localtime(&timer);

	snprintf(time_info, 25, "[%d-%d-%d %d:%d:%d]", (local_time->tm_year+1900), local_time->tm_mon,
		local_time->tm_mday, local_time->tm_hour, local_time->tm_min, local_time->tm_sec); //[AAAA-MM-DD HH-MM-SS]
}

void w_log(const char *error, const char *action, const char *log_file, short int enter){

	char time_info[25];

	g_time(time_info);

	char *_enter[4]={"%s -> %s : %s\n", "%s -> %s : %s\n\n", "\n\n%s -> %s : %s\n\n", "%s -> %s : %s"};

	size_t len=snprintf(NULL, 0, _enter[enter], time_info, action, error);

	char *log=(char*)malloc(len*sizeof(char)+1);

	snprintf(log, 256, _enter[enter], time_info, action, error);	

	FILE *file=fopen(log_file, "a");

	if(file==NULL){

		mkdir("logs", S_IRWXG);

		file=freopen(log_file, "a", file);
	
	}else{

		fprintf(file, "%s", log);

		file=freopen(LOG_ALL, "a", file);

		fprintf(file, "%s", log);

		printf("%s", log);
	}

	free(log);

	fclose(file);
}

void w_connection_log(const char *error,const char *client_addr, const char *action, const char *log_file, short int enter){

	char time_info[25];

	g_time(time_info);

	char *_enter[4]={"%s -> %s : %s\n", "%s -> %s : %s\n\n", "\n\n%s -> %s : %s\n\n", "%s -> %s : %s"};

	size_t len=snprintf(NULL, 0, _enter[enter], time_info, action, client_addr, error);

	char *log=(char*)malloc(len*sizeof(char)+1);

	snprintf(log, 256, _enter[enter], time_info, action, client_addr, error);

	FILE *file=fopen(log_file, "a");

	if(file==NULL){

		mkdir("logs", S_IRWXG);

		file=freopen(log_file, "a", file);
	
	}else{

		fprintf(file, "%s\n", log);

		file=freopen(LOG_ALL, "a", file);

		fprintf(file, "%s\n", log);

		printf("%s\n", log);
	}

	free(log);

	fclose(file);
}