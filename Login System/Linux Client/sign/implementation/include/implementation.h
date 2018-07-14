#ifndef IMPLEMENTATION_H
#define IMPLEMENTATION_H

#include <stdio.h>
#include <string.h>

#define NUMBERS 		"0123456789"
#define UPP_ALPHABET 	"ABCDEFGHIJKLMNOPQRSTUVXWYZ"
#define ESPECIAL_CHARS 	"'!@#$%&*()_-+={[]}?/;:><.,|/\\"

extern void get_string(char *_string, size_t len);

extern int find_char(const char *_string, const char c);

extern short int get_name(char *name);
extern short int get_username(char *username);
extern short int get_password(char *password);

#endif //IMPLEMENTATION_H