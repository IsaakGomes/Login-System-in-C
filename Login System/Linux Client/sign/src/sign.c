#include "sign.h"

void sign_in(){

	struct sign_in_credentials cred; 

	int response;

	do{

		printf("\n\nusername ->");
		get_string(cred.username, 16);

		printf("password ->");
		get_string(cred.password, 65);

		//...

		printf("\n\n[-] - Aguarde um momento...");

		int sockfd=start_connection();

		if(sockfd==-1){

			printf("\n\n[X] - Error ao se conectar com o servidor. Tente novamente.\n\n");

			close(sockfd);

			break;
		
		}else{

			printf("\n\n[V] - Conexão com o servidor: OK!\n");
		}

		enum request rq=SIGN_IN;

		if(send(sockfd, (const char*)&rq, sizeof(enum request), 0)==-1){

			printf("\n\n[X] - Error de conexão. Tente novamente.\n\n");

			close(sockfd);

			break;

		}else{

			printf("[v] - Enviando solicitação de login para o servidor\n");
		}

		if(send(sockfd, (const char*)&cred, sizeof(struct sign_in_credentials), 0)==-1){

			printf("[X] - Error de conexão. Tente novamente.\n\n");
		
			close(sockfd);

			break;

		}else{

			printf("[V] - Enviando credenciais de login para o servidor...\n");
		}

		if(recv(sockfd, (char*)&response, sizeof(int), 0)==-1){

			printf("[X] - Error de conexão. Tente novamente.\n\n");

			close(sockfd);

			break;

		}else{

			if(response==-1){

				printf("[X] - Servidor fora do ar...\n");
				printf(" |-> Possível causa: O servidor pode está em");
				printf(" manutenção.\n\n");

				close(sockfd);

				exit(0);
			
			}else if(response==-2){

				printf("[X] - Credenciais de login incorretas.\n[-] - Tente novamanete.\n\n");

				close(sockfd);
			
				break;

			}else{

				printf("[V] - Login realizado com sucesso\n\n");

				close(sockfd);
				
				exit(EXIT_SUCCESS);
			}
		}

	}while(1);
}

void sign_up(){

	struct sign_up_credentials cred;

	short int rv;

	int response;

	do{

		do{

			printf("\n\nDigite seu nome completo >");
			rv=get_name(cred.name);

			if(rv==1){

				printf("[X] - Atenção: O nome que você forneceu é");
				printf(" muito grande. Tente abreavia-lo.\n\n");

			}else if(rv==2){

				printf("[X] - Por favor, forneça seu nome verdadeiro.\n\n");
			
			}else if(rv==3){

				printf("[X] - Por favor, forneça seu nome completo.\n\n");
			
			}else{

				printf("[V] - Nome: Ok\n");
			}

		}while(rv!=0);

		printf("\n\n+============-Username(nome de usuário)-=============+\n");
		printf("| Não é permitido username com espaço em branco......|\n");
		printf("| É permitido o uso de caracters especiais e numeros.|\n");
		printf("| O maximo de caracteres para o username é 15........|\n");
		printf("| O mínimo de caracteres para o username é 3.........|\n");
		printf("+====================================================+\n\n");

		do{

			printf("Digite um username (nome de usuario)>");
			rv=get_username(cred.username);

			if(rv==1){

				printf("[X] - O username não pode ter mais de 15 caracteres.\n\n");
			
			}else if(rv==2){

				printf("[X] - O username não pode ter menos de 3 caracteres.\n\n");
			
			}else if(rv==3){

				printf("[X] - O username não pode conter espaços em branco.\n\n");
			
			}else{

				printf("[V] - Username: Ok!\n");
			}

		}while(rv!=0);

		printf("\n\n+===============--------Senha--------================+\n");
		printf("| Use combinações de letras em maiusculo e minusculo |\n");
		printf("| Use também caracteres especiais e números..........|\n");
		printf("| O maximo de caracteres para a senha é 100..........|\n");
		printf("| O mínimo de caracteres para a senha é 8............|\n");
		printf("+====================================================+\n\n");

		do{

			printf("Digite uma senha >");
			rv=get_password(cred.password);

			if(rv==1){

				printf("[x] - A senha não deverá conter mais do que 100 caracteres.\n\n");
			
			}else if(rv==2){

				printf("[x] - A senha não deverá conter menos do que 8 caracteres.\n\n");

			}else if(rv==3){

				printf("[X] - A senha deverá conter pelo menos um caractere epecial.\n\n");
			
			}else if(rv==4){

				printf("[X] - A senha deverá conter pelo menos um número.\n\n");

			}else if(rv==5){

				printf("[X] - A senha deverá conter pelo menos uma letra em maiusculo.\n\n");

			}else{

				printf("[V] - Senha: Ok!\n");
			}

		}while(rv!=0);

		do{

			printf("\n+=Informe seu sexo=+\n");
			printf("+==================+\n");
			printf("| Masculino....[1] |\n");
			printf("| Feminino.....[2] |\n");
			printf("| Outro........[3] |\n");
			printf("+==================+\n>");

			rv=getchar();
			__fpurge(stdin);

			switch(rv){

				case '1':

					cred.genre=MALE;

					break;

				case '2':

					cred.genre=FEMALE;

					break;

				case '3':

					cred.genre=OTHER;

					break;

				default:

					printf("Opção incorreta\n\n");
					break;
			}
		
		}while(rv!='1' && rv!='2' && rv!='3');

		printf("\n\n%c\n", cred.genre);

		printf("\n\n[-] - Aguarde um momento...");

		int sockfd=start_connection();

		if(sockfd==-1){

			printf("\n\n[X] - Error ao se conectar com o servidor. Tente novamente.\n\n");

			close(sockfd);

			break;
			
		}else{

			printf("\n\n[V] - Conexão com o servidor: OK!\n");
		}

		enum request rq=SIGN_UP;

		if(send(sockfd, (const char*)&rq, sizeof(enum request), 0)==-1){

			printf("\n\n[X] - Error de conexão. Tente novamente.\n\n");

			close(sockfd);

			break;

		}else{

			printf("[v] - Enviando solicitação para o servidor\n");
		}

		if(send(sockfd, (const char*)&cred, sizeof(struct sign_up_credentials), 0)==-1){

			printf("[X] - Error de conexão. Tente novamente.\n\n");
			
			close(sockfd);

			break;

		}else{

			printf("[V] - Enviando dados para o servidor...\n");
		}

		if(recv(sockfd, (char*)&response, sizeof(int), 0)==-1){

			printf("[X] - Error de conexão. Tente novamente.\n\n");

			close(sockfd);

			break;

		}else{

			if(response==-1){

				printf("[X] - Servidor fora do ar...\n");
				printf("| |--> Possível causa: O servidor pode está em");
				printf(" manutenção.\n\n");

				close(sockfd);

				exit(0);
				
			}else if(response==-2){

				printf("[X] - O username fornecido já está em uso.\nTente outro.\n\n");

				close(sockfd);
				
				break;

			}else{

				printf("[V] - Conta criada com sucesso.\n\n");

				close(sockfd);
					
				break;
			}
		}

	}while(response!=0);
}