#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int browserPID = -1;
int textEditorPID = -1;
int terminalPID = -1;

int browserStatus = 999;
int textEditorStatus = 999;
int terminalStatus = 999;

//utilidade
char * getStatusToString (int status){
	
	if (status == 0){
		return "Concluído";
	}
	else {
		return "arrumar";
	}
	
}

int menu (){
	
	int option = 0;
	
			
		printf ("<<<<Applications Menu>>>>\n");
		printf ("\t1) Web Browser\n");
		printf ("\t2) Text Editor\n");
		printf ("\t3) Terminal\n");
		printf ("\t4) Finalizar processo\n");
		printf ("\t5) Quit\n");
		printf ("Option: ");
		scanf ("%i", &option);
		printf ("\n");
	
	return option;
	
}

void web_browser(){
	pid_t pid;
	int status;
	
	pid = fork();	//cria filho
	
	if (pid == 0){		//filho
		
			char url[50];
			printf ("Digite a url desejada: ");
			scanf ("%s", url);
			execlp("firefox", "--new-window", url, NULL);
			browserStatus = 1;
			browserPID = getpid();
			break;
		
	}
	
	else if (pid < 0){	//erro
		
		browserStatus = -1;
		
	}
	
}

void text_editor(){
	printf ("teste\n");
}

void terminal(){
	printf ("teste\n");
}

void* kill_process(void *param){
	
	pid_t pid;
	int status;
	
	int killProcess;
	
	pid = fork();
	
	if (pid == 0){	
	
	printf ("Digite qual processo deve ser terminado: ");
	scanf ("%i", &killProcess);
	
		switch (killProcess){
			case 1:
				system ("kill", browserPID, NULL);
				break;
			case 2:
				system ("kill", textEditorPID, NULL);
				break;
			
			case 3:
				system ("kill", terminalPID, NULL);
				break;
			
			default:
			
				printf ("Opção inválida");
		}
	
	}
	
	else if (pid < 0){
		//deu ruim
	}
	
	else {
		
			/* Código do processo pai continua aqui */
		/* Aguarda processo filho terminar e recebe status */
		wait(& status);
 
		/* Verifica se o processo filho terminou normalmente */
		/* Caso tenha terminado, imprime o status de saída do filho */
		if( WIFEXITED(status) )
			//fprintf(stdout, "Status de saida do filho: %d.\n", WEXITSTATUS(status) );
			int saidaFilho = WEXITSTATUS(status);
		else
			fprintf(stdout, "Processo filho terminou de forma anormal.\n");
 
		/* Imprime dados na tela */
		fprintf(stdout, "Processo pai. meu PID: %d.\n", (int)getpid() );
		fprintf(stdout, "Processo pai. PID do meu filho: %d.\n", (int)child_pid );
		fprintf(stdout, "Processo pai. local_var: %d.\n", local_var );
		fprintf(stdout, "Processo pai. global_var: %d.\n", global_var );
		
	}	
	
}

void option_call (int option){
	
	int te;
	pthread_t tids;
	
	/*
	if (option == 1)
		web_browser();			//chamar thread
	else if (option == 2)
		text_editor();
	else if (option == 3)
		terminal();
	else if (option == 4)
		kill_process();
	
	*/
	
	if (option == 1)
		te = pthread_create(&tids, NULL, &web_browser());			 
	else if (option == 2)
		text_editor();
	else if (option == 3)
		terminal();
	else if (option == 4)
		kill_process();
	
	
}


int main(){
	
	int option = 0;
	
	while ((option = menu())!=5){
		
		option_call(option);
	
	}
	
	
}
