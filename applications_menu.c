#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <errno.h>
#include <sys/wait.h>
#include <signal.h>

int browserPID = 0;
int textEditorPID = 0;
int terminalPID = 0;
int finalizarPID = 0;

char * browserStatus;
char * textEditorStatus;
char * terminalStatus;
char * finalizarStatus;


void menu (){
	
	
	
			
		printf ("<<<<Applications Menu>>>>\n");
		if (strncmp(browserStatus, "exec", 2) == 0)
			printf ("\t1) Web Browser (executando, PID=%i)\n", browserPID);
		else
			printf ("\t1) Web Browser %s\n", browserStatus);
		
		if (strncmp(textEditorStatus, "exec", 2) == 0)
			printf ("\t2) Text Editor (executando, PID=%i)\n", textEditorPID);
		else
			printf ("\t2) Text Editor %s\n", textEditorStatus);
		
		if (strncmp(terminalStatus, "exec", 2) == 0)
			printf ("\t3) Terminal (executando, PID=%i)\n", terminalPID);
		else
			printf ("\t3) Terminal %s\n", terminalStatus);

		if (strncmp(finalizarStatus, "exec", 2) == 0)
			printf ("\t4) Finalizar processo (executando, PID=%i)\n", finalizarPID);
		else
			printf ("\t4) Finalizar processo %s\n", finalizarStatus);

		printf ("\t5) Quit\n");
		
	
}


void* web_browser(void *param){
	pid_t pid;
	int status;
	
	pid = fork();	//cria filho
	
	if (pid == 0){		//filho
			
			//printf ("PID browser: %i", getpid());
			char url[50];
			printf ("Digite a url desejada: ");
			scanf ("%s", url);
			execlp("firefox", "--new-window", url, NULL);
			
					
		
	}
	
	else if (pid < 0){	//erro
		
		browserStatus = "falhou";
		
	}
	
	else {
		
		
		browserStatus = "executando";				
		browserPID = pid;

		
			/* Código do processo pai continua aqui */
		/* Aguarda processo filho terminar e recebe status */
		wait(&status);

 		//verifica se processo filho recebeu sinal para terminação
		if (WIFSIGNALED(status))
			browserStatus = "abortado";		

		/* Verifica se o processo filho terminou normalmente */
		
		if( WIFEXITED(status) ){
			
			int saidaFilho;
			saidaFilho = WEXITSTATUS(status);
			
			if (saidaFilho == 0){
				browserStatus = "concluido";
			}
			else {
				browserStatus = "falha";
			}
		}
		else{
			fprintf(stdout, "Processo filho terminou de forma anormal.\n");
			browserStatus = "abortado";
		}
 
		/* Imprime dados na tela */	
		
		fprintf(stdout, "Processo pai (webBrowser) encerrando. meu PID: %d.\n", (int)getpid() );
		
		
	}
	
}

void* text_editor(void *param){
	pid_t pid;
	int status;

	pid = fork();
	
	if (pid == 0){		//filho
			
			
		execlp("/usr/bin/gedit","gedit","newtext.txt",NULL);
			
					
		
	}
	
	else if (pid < 0){	//erro
		
		textEditorStatus = "falhou";
		
	}
	
	else {
		
		
		textEditorStatus = "executando";				
		textEditorPID = pid;

		
			/* Código do processo pai continua aqui */
		/* Aguarda processo filho terminar e recebe status */
		wait(&status);

 		//verifica se processo filho recebeu sinal para terminação
		if (WIFSIGNALED(status))
			textEditorStatus = "abortado";		

		/* Verifica se o processo filho terminou normalmente */
		
		if( WIFEXITED(status) ){
			
			int saidaFilho;
			saidaFilho = WEXITSTATUS(status);
			
			if (saidaFilho == 0){
				textEditorStatus = "concluido";
			}
			else {
				textEditorStatus = "falha";
			}
		}
		else{
			fprintf(stdout, "Processo filho terminou de forma anormal.\n");
			textEditorStatus = "abortado";
		}
 
		/* Imprime dados na tela */	
		
		fprintf(stdout, "Processo pai (textEditor) encerrando. meu PID: %d.\n", (int)getpid() );
		
		
	}

}

void* terminal(void *param){
	pid_t pid;
	int status;

	pid = fork();
	
	if (pid == 0){		//filho
			
		terminalStatus = "executando";	
		system("gnome-terminal");
			
					
		
	}
	
	else if (pid < 0){	//erro
		
		terminalStatus = "falhou";
		
	}
	
	else {
		
		
		terminalStatus = "executando";				
		terminalPID = pid;

		
			/* Código do processo pai continua aqui */
		/* Aguarda processo filho terminar e recebe status */
		wait(&status);

 		//verifica se processo filho recebeu sinal para terminação
		if (WIFSIGNALED(status))
			terminalStatus = "abortado";		

		/* Verifica se o processo filho terminou normalmente */
		
		if( WIFEXITED(status) ){
			
			int saidaFilho;
			saidaFilho = WEXITSTATUS(status);
			
			if (saidaFilho == 0){
				terminalStatus = "concluido";
			}
			else {
				terminalStatus = "falha";
			}
		}
		else{
			fprintf(stdout, "Processo filho terminou de forma anormal.\n");
			terminalStatus = "abortado";
		}
 
		/* Imprime dados na tela */	
		
		fprintf(stdout, "Processo pai (terminal) encerrando. meu PID: %d.\n", (int)getpid() );
		
		
	}
}

void* kill_process(void *param){
	
	pid_t pid;
	int status;
	
	int killProcess;
	
	pid = fork();
	
	if (pid == 0){	
	
	printf ("Digite qual processo deve ser terminado: ");
	scanf ("%i", &killProcess);
	
	/*
	char killedPID[12];
	
		switch (killProcess){
			case 1:
				//killedPID = (int)browserPID;
				sprintf (killedPID, "%d", (int)browserPID);
				//execlp ("kill", killedPID, NULL);
				kill(browserPID, SIGTERM);
				break;
			case 2:
				//killedPID = (int)browserPID;
				sprintf (killedPID, "%d", (int)textEditorPID);
				//execlp ("kill", killedPID, NULL);
				kill(textEditorPID, SIGTERM);
				break;
			
			case 3:
				//killedPID = (int)browserPID;
				sprintf (killedPID, "%d", (int)terminalPID);
				//execlp ("kill", killedPID, NULL);
				kill(terminalPID, SIGTERM);
				break;
			
			default:
			
				printf ("Opção inválida");
		} */

		if (killProcess == 1)
			kill(browserPID, SIGTERM);
		else if (killProcess == 2)
			kill(textEditorPID, SIGTERM);
		else if (killProcess == 3)
			kill(terminalPID, SIGTERM);
	
	}
	
	else if (pid < 0){
		finalizarStatus = "falhou";
	}
	
	else {
		
		finalizarStatus = "executando";				
		finalizarPID = pid;

	
			/* Código do processo pai continua aqui */
		/* Aguarda processo filho terminar e recebe status */
		wait(&status);
 		
		if (WIFSIGNALED(status))
			finalizarStatus = "abortado";		
	
		/* Verifica se o processo filho terminou normalmente */
		/* Caso tenha terminado, imprime o status de saída do filho */
		if( WIFEXITED(status) ){

			int saidaFilho;
			saidaFilho = WEXITSTATUS(status);
			
			if (saidaFilho == 0){
				finalizarStatus = "concluido";
			}
			else {
				finalizarStatus = "falha";
			}		
	
		}
		else{
			finalizarStatus = "abortado";
			fprintf(stdout, "Processo filho terminou de forma anormal2.\n");
			
		}
 
		/* Imprime dados na tela */
		fprintf(stdout, "Processo pai (killProcess) terminando. meu PID: %d.\n", (int)getpid() );
		
	}	
	
}

void option_call (int option){
	
	int te;
	pthread_t tids;
	
	
		
	
	if (option == 1){
		
		te = pthread_create(&tids, NULL, &web_browser, NULL);
	}		 
	else if (option == 2)
		te = pthread_create(&tids, NULL, &text_editor, NULL);
	else if (option == 3)
		te = pthread_create(&tids, NULL, &terminal, NULL);
	else if (option == 4)
		
		te = pthread_create(&tids, NULL, &kill_process, NULL);
	
	
}

void tratador (int signum){
	menu();
}

int main(){
	
	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));

	sa.sa_handler = &tratador;

	if (sigaction(SIGINT, &sa, NULL)!=0){
		perror ("Falha ao tratar SIGINT");
		exit (-1);
	}
	
	if (sigaction(SIGCHLD, &sa, NULL)!=0){
		perror ("Falha ao tratar SIGINT");
		exit (-1);
	}

	browserStatus = "";
	textEditorStatus = "";
	terminalStatus = "";
	finalizarStatus = "";

	int option = 0;
	
	while (option != 5){
		
		menu();
		printf ("Option: ");
		scanf ("%i", &option);
		printf ("\n");

		option_call(option);
		sleep (5);
	
	}
	
	
}
