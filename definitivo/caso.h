#ifndef __CASO__
#define __CASO__


#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define MAX 10 
#define DIM 20 
#define maxn 20

typedef int bool;
enum { false, true };


typedef struct string
{
	char* a[20];
};

typedef struct Processo
{
	int pid;
	int ppid;
	//int tempo_esec;
	//bool visitato;
	bool chiuso;
	//bool pausa;
	char nome_processo[20];
	int figli[20];
	int fd[2];
};


struct Processo lista_processi[10]; 
int lista[10];
int lista_pipe[10][2];


/*FUNZIONI DI SUPPORTO Processo proc*/

bool get_string(char string1[]);
bool string_compare(char string1[],char string2[]);

/* FUNZIONI BASE DEL PROGETTO*/

void phelp(); //stampa la lista dei comandi disponibili
void plist(int n); //elenca i processi generati dalla shell
bool pnew(char nome[], int n); //crea un nuovo processo di nome <nome> e restituisce true se ce la fa, false altrimenti n è il buffer del vettore dei processi
void process_info(int n, char nome[]); //fornisce informazioni sul processo di nome <nome>
bool chiudi_processo (int n, char nome[]); //chiede al processo di nome <nome> di chiudersi

/*FUNZIONI AVANZATE DEL PROGETTO*/

bool pspawn( char nome[],int n); //chiede al processo di nome <nome> di clonarsi creando un processo di nome <nome_i> con i progressivo
void prmall(char nome[]); //chiede al processo di nome <nome> di chiudersi chiudendo anche tutti i suoi cloni
void ptree(); //mostra la gerarchia dei processi attivi 



#endif

