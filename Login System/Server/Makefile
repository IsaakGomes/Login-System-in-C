#=======Server=======#

#1 logs
gcc -Wall -c logs.c

#2 mysql

gcc -Wall -I "mysql-connector-c/include" -L "mysql-connector-c/lib/libmysqlclient.so" -I "/home/isaak/Documents/C programming/Login System/Server/logs" -c mysql2.c

#3 server

gcc -Wall -I "/home/isaak/Documents/C programming/Login System/Server/logs" -I "/home/isaak/Documents/C programming/Login System/Server/mysql" -I "/home/isaak/Documents/C programming/Login System/Server/sign" -I "/home/isaak/Documents/C programming/Login System/Server/mysql/mysql-connector-c/include" -c server.c 

#4 sign

gcc -Wall -I "/home/isaak/Documents/C programming/Login System/Server/logs" -I "/home/isaak/Documents/C programming/Login System/Server/mysql/mysql-connector-c/include" -L "/home/isaak/Documents/C programming/Login System/Server/mysql/mysql-connector-c/lib/libmysqlclient.so" -I "/home/isaak/Documents/C programming/Login System/Server/mysql" -c sign.c -lcrypto

#--------------------------------------------------------------------------------------------------------------------------

#5 main

gcc -Wall -I "server" -I "logs" -I "sign" -I "mysql" -I "/home/isaak/Documents/C programming/Login System/Server/mysql/mysql-connector-c/include" -c main.c

#6 Server

gcc -Wall "logs/logs.o" "mysql/mysql2.o" "server/server.o" "sign/sign.o" "mysql/mysql-connector-c/lib/libmysqlclient.so" main.o -lcrypto -o Server

#=======Client=======#

#1 server
gcc -Wall -c server.c

#2 implementation
gcc -Wall -c implementation.c

#3 sign
gcc -Wall -I "implementation" -I "/home/isaak/Documents/C programming/Login System/Linux Client/server" -c sign.c

#4 main.c
gcc -Wall -I "server" -I "sign" -I "sign/implementation" -c main.c

#5 main.o
gcc -Wall "server/server.o" "sign/sign.o" "sign/implementation/implementation.o" main.o -o Client