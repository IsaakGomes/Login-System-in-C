#ifndef LOGS_H
#define LOGS_H

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define LOG_SRV 	"logs/server_logs.txt"
#define LOG_SRV_C 	"logs/connection_logs.txt"
#define LOG_DB 		"logs/database_connection_logs.txt"
#define LOG_ALL		"logs/all_logs.txt"

extern void g_time(char *timer_info);
extern void w_log(const char *error, const char *action, const char *log_file, short int enter);
extern void w_connection_log(const char *error, const char *client_addr, const char *action, const char *log_file, short int enter);

#endif