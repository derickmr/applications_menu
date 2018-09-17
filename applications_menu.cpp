#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int browserPID = -1;
int textEditorPID = -1;
int terminalPID = -1;

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
	int pid;
	pid = fork();
	
	switch (pid){
		case 0:
			char url[50];
			printf ("Digite a url desejada: ");
			scanf ("%s", url);
			execlp("firefox", "--new-window", url, NULL);
			browserPID = getpid();
			break;
	}
	
}

void text_editor(){
	printf ("teste\n");
}

void terminal(){
	printf ("teste\n");
}

void kill_process(){
	
	int killProcess;
	
	printf ("Digite qual processo deve ser terminado: ");
	scanf ("%i", &killProcess);
	
	switch (killProcess){
		case 1:
			sudokill(browserPID);
			break;
		case 2:
			sudokill(textEditorPID);
			break;
			
		case 3:
			sudokill(terminalPID);
			break;
			
		default:
			
			printf ("Opção inválida");
	}
	
}

void option_call (int option){
	
	if (option == 1)
		web_browser();
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
