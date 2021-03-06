#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include "caso.h"

int global_variable=0;
int status;

int scrivi=1;
int LEGGI=0;

/* FUNZIONI DI SUPPORTO*/

bool string_compare(char string1[],char string2[])
{
	int i=0;
	for(; string1[i] != '\0' || string2[i]!='\0'; i++)
	{	
		//printf("%d\n",i);
		//printf("string1= %c, string2=%c \n",string1[i],string2[i]);
		if(string1[i]!=string2[i])
		{
		return false;
		}
	}
return true;
}


int leggi(int fd){
	int vletto = 0;
	vletto = read(lista_processi[n].fd[LEGGI],&buf,sizeof(int));
	printf("Ho letto %d\n",vletto);
	if (vletto != 0)
	{
		return 0;
	}
	return 1;
}

/* FUNZIONI BASE DEL PROGETTO*/

void phelp()
{
	system("cat phelp.txt");
}


void plist(int n)
{
	printf("n in plist: %d\n",n);	
	printf(" Lista dei processi generati: \n");
	for(int i=0;i<=n;i++)
	{
		if(lista_processi[i].chiuso!=true)
		{
			printf("Processo %d ",i);
			printf("nome= %s - ",lista_processi[i].nome_processo);
			printf("pid= %d - ",lista_processi[i].pid);
			printf("ppid= %d ; \n",lista_processi[i].ppid);	
		}
		else
		{
			printf("Processo %d ",i);
			printf("nome= %s - ",lista_processi[i].nome_processo);
			printf("pid= x - ");
			printf("ppid= x ; \n");	
		}
	}
}


bool pnew(char nome[],int n)
{	

	printf("n in pnew: %d\n",n);
	pid_t childPID 	; 
	pipe(lista_processi[n].fd); //SE LA METTO SOTTO LA FORK ENTRA NEL WHILE
	childPID = fork();
	
	int comando=-1;
	if (childPID >= 0)
	{ // fork's success
		if (childPID == 0)
        	{ // child process
			global_variable++;
			close(lista_processi[n].fd[scrivi]);
			printf("il pid del processo figlio è %d \n", getpid());
			printf("e il processo del padre è %d \n",getppid());
			printf("metto in pausa il figlio\n");
			
			valore = leggi(lista_processi[n].fd);
			if (valore!=0)
			{
				while(1)
				{
					Sleep();
				}
			}		
			else
			{
			//while(1) //dormo fino a quando non do la condizione
			//{
				int buf=-1;
				comando=read(lista_processi[n].fd[LEGGI],&buf,sizeof(int));
				//printf("%d",comando);
				//printf("questo è il numero stampato %d\n",buf);
				if(comando==0)
				{
					printf("diocane");
				}
					/*
					char nome2[strlen(nome)+2];
					strcpy(nome2,nome);
					char a=(char)n+1;
					char ciao='_';
					strcat(nome2,ciao);
					strcat(nome2,a);
					//clonax
					//pnew(nome2,n);
					
					printf("forse faccio cose");
				}
				else if(comando==1)
				{
					//ucciditi
				}
				else if(comando==2);
				{
					//uccidi te e tutta la tua famiglia
				}*/
				//controlla la pipe 
				//attendo la pipe (uccidi o clona o uccidi i figli)
			//close(lista_pipe[n][LEGGI]);
			}
			printf("sono uscito dal while");
			}
			else 
			{ // parent process

				strcpy(lista_processi[n].nome_processo,nome);
				lista_processi[n].pid=childPID;
				lista_processi[n].ppid=getpid();
				lista_processi[n].chiuso=false;
				system("echo processo creato");		   		    
        		};	
        }
	else 
	{ // fork's failure
		printf("\nFork failure!\n");
		return false;
	}
	printf("alla fine di pnew n: %d\n",n);
	return true;

}


void process_info(int n, char nome[])
{
	for(int i=0; i<n; i++)
	{
		if (string_compare(lista_processi[i].nome_processo, nome) )
		{
			if(lista_processi[i].chiuso!=true)
			{
				printf("pid= %d - ",lista_processi[i].pid);
				printf("ppid= %d ; \n",lista_processi[i].ppid);	
			}
			else
			{
				printf("pid= x - ");
				printf("ppid= x - processo chiuso; \n");	
			}
		}
	}
}


bool chiudi_processo (int n,char nome[])
{

	for(int i=0; i<n; i++) //cerca il processo di nome nome 
	{
		if (string_compare(lista_processi[i].nome_processo, nome)) //processo trovato, KILL 
		{
			
			kill(lista_processi[i].pid,SIGKILL);
			//i figli saranno orfani
			lista_processi[i].chiuso=true;			
			//lista_processi[i].pid=0;
			//lista_processi[i].ppid=0;
			return true;
		}
	}
	return false;
}


/*FUNZIONI AVANZATE DEL PROGETTO*/
bool pspawn(char nome[],int n) //chiede al processo di nome <nome> di clonarsi creando un processo di nome <nome_i> con i progressivo
{
	//for(int i=0; i<=n; i++) //cerco il processo
	//{
		//if (strcmp(lista_processi[i].nome_processo, nome))
			//{
				int a=0;
				close(lista_processi[n].fd[LEGGI]);
				//metto in wait il padre e faccio riprendere il figlio
				printf("ora riprendo il processo\n");
				write(lista_processi[n].fd[scrivi],&a,sizeof(int));
				close(lista_processi[n].fd[scrivi]);
				//printf(lista_processi[i].fd[scrivi]);
				//modifico la pipe di quel processo e attendo che il figlio si cloni
				//kill(lista_processi[i].pid,SIGCONT);
				//close(lista_processi[i].fd[scrivi]);	
			return true;
			//}
	//}
//return false;
}


void prmall(char nome[]); //chiede al processo di nome <nome> di chiudersi chiudendo anche tutti i suoi cloni

void ptree(); //mostra la gerarchia dei processi attivi 
