#ifndef __PMANAGER__
#define __PMANAGER__


#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define MAX 10 		//dimensioni delle liste (processi e pipe)
#define  DIM_NOME 50		//dimensione del nome di un processo 


/*
*Creazione del tipo di dato booleano 
*/
typedef int bool;		 
enum { false, true };


/*
*Creazione del tipo di  dato Processo
*/
typedef struct Processo		
{
	int pid;
	int ppid;
	bool chiuso;
	bool visitato;			//attributo di stato che indica se il processo è stato chiuso o è attivo 
	char nome_processo[DIM_NOME];
	int figli[MAX];
	int fd[2];			//pipe tra un processo e suo padre
	int df[2];
} p;


struct Processo lista_processi[MAX]; 	//lista di elementi di tipo Processo
int lista_pipe[MAX][2];			//lista pipe (non ancora usata)


/*FUNZIONI DI SUPPORTO Processo proc*/

bool string_compare(char string1[],char string2[]); 	//confronta due array di caratteri
bool controlla_nome(char nome[], int dim);
void nome_progressivo(char nome[], int cont);
void trova_nome_padre(int pid, char nome_padre[], int n);

/* FUNZIONI BASE DEL PROGETTO*/

void phelp(); //stampa la lista dei comandi disponibili
void plist(int n); //elenca i processi generati dalla shell
bool pnew(char nome[], int n); //crea un nuovo processo di nome <nome> e restituisce true se ce la fa, false altrimenti n è il buffer del vettore dei processi
void process_info(int n, char nome[]); //fornisce informazioni sul processo di nome <nome>
bool chiudi_processo (int n, char nome[]); //chiede al processo di nome <nome> di chiudersi

/*FUNZIONI AVANZATE DEL PROGETTO*/

int pspawn( char nome[],int n,int *dove_sono); //chiede al processo di nome <nome> di clonarsi creando un processo di nome <nome_i> con i progressivo
void prmall(char nome[]); //chiede al processo di nome <nome> di chiudersi chiudendo anche tutti i suoi cloni
void ptree(); //mostra la gerarchia dei processi attivi 



#endif

