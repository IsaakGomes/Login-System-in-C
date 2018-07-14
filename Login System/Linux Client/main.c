#include "sign.h"
#include <stdio.h>

void menu(){

	unsigned char opc;

	do{

		printf("+=====================+\n");
		printf("| Sign in.........[1] |\n");
		printf("| Sign up.........[2] |\n");
		printf("| Exit............[3] |\n");
		printf("+=====================+\n->");

		opc=getchar();
		__fpurge(stdin);

		switch(opc){

			case '1':

				sign_in();

				break;

			case '2':

				sign_up();

				break;

			case '3':

				break;

			default:

				printf("Opção incorreta...\n\n");
		}

	}while(opc!='3');
}

int main(void){

	menu();

	return 0;
}