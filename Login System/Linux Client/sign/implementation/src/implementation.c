#include "implementation.h"

void get_string(char *_string, size_t input_max_size){

	fgets(_string, input_max_size, stdin);

	size_t len=strlen(_string);

	_string[len-1]='\0';
}

int find_char(const char *_string, const char c){

	int rv=-1;

	for(unsigned int i=0; i<strlen(_string); i++){

		if(_string[i]==c){

			rv=i;

			break;
		}
	}

	return rv;
}

int find_chars(const char *_string, const char *chars){

	int rv=-1;

	for(unsigned int x=0; x<strlen(_string); x++){

		for(unsigned int y=0; y<strlen(chars); y++){

			if(_string[x]==chars[y]){

				rv=x;
			}
		}
	}

	return rv;
}

short int get_name(char *name){

	get_string(name, 256);

	short int rv;

	size_t len=strlen(name);

	if(strlen(name)>255){

		rv=1;
	
	}else if(len<3){

		rv=2;

	}else if(find_char(name, ' ')==-1){

		rv=3;

	}else{

		rv=0;
	}

	return rv;
}

short int get_username(char *username){

	get_string(username, 16);

	short int rv;

	if(strlen(username)>15){

		rv=1;

	}else if(strlen(username)<3){

		rv=2;

	}else if(find_char(username, ' ')!=-1){

		rv=3;
	
	}else{

		rv=0;
	}

	return rv;
}

short int get_password(char *password){

	get_string(password, 101);

	short int rv;

	if(strlen(password)>100){

		rv=1;
	
	}else if(strlen(password)<8){

		rv=2;
	
	}else if(find_chars(password, ESPECIAL_CHARS)==-1){

		rv=3;

	}else if(find_chars(password, NUMBERS)==-1){

		rv=4;

	}else if(find_chars(password, UPP_ALPHABET)==-1){

		rv=5;

	}else{

		rv=0;
	}

	return rv;
}