#ifndef SIGN_H
#define SIGN_H

#include <stdio.h>
#include <sys/socket.h>

#include "server.h"
#include "implementation.h"

struct sign_in_credentials{

	char username[16], password[101];
};

struct sign_up_credentials{

	char name[256];
	char username[16], password[129];

	enum __genre{MALE=77, FEMALE=70, OTHER=79}genre; //77='M'...70='F'...79='O'
};

enum request{SIGN_IN, SIGN_UP, _ERROR_};

extern void sign_in();
extern void sign_up();

#endif //SIGN_H
