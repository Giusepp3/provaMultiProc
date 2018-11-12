#ifndef _HEADER_H
#define _HEADER_H
//calcolo della media di N valori
//librerie
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <stdlib.h>

//macro
#define DIM_BUF 5
#define NUM_PROC 2
#define SPAZIO_DISP DIM_BUF
#define MESS_DISP 0
#define FTOK_PATH '.'
#define FTOK_CHAR 'a'
#define N_MESS 10
#define N_SEMS 1
#define PERM 777

//prototipi
void wait_sem(int semid,int semnum,int n);
void signal_sem(int semid,int semnum,int n);
void prod(int* p_shm,int ds_sem);
void cons(int* p_shm,int ds_sem);

//buffer di memoria

typedef struct {
	int testa;
	int coda;
	int elem[DIM_BUF];
}buffer_circ;


#endif
