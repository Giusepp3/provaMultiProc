#include <string.h>
#include "header.h"

int main(){
	key_t shm_key = ftok(FTOK_PATH,FTOK_CHAR);
	int ds_shm = shmget(shm_key,sizeof(int),IPC_CREAT | PERM);
	printf("[CONS %d]: creato il descrittore per la memoria condivisa\n",getpid());


	if(ds_shm<0){
		char * err = NULL;
		strcat(err,"[CONS ");
		char * pid = NULL;
		*pid = (char)getpid();
		strcat(err,pid);
		strcat(err,"]: errore shm\n");
		perror(err);
		_exit(-2);
	}

	buffer_circ* buf = (buffer_circ*) shmat(ds_shm,NULL,0);

	key_t sem_key = ftok(FTOK_PATH,FTOK_CHAR);
	printf("[CONS %d]: creata la chiave per il semaforo\n",getpid());
	int ds_sem = semget(sem_key,N_SEMS,IPC_CREAT | PERM);
	printf("[CONS %d]: creato il descrittore per il semaforo\n",getpid());

	for(int i=0; i<N_MESS;i++){
		wait_sem(ds_sem,MESS_DISP,1);
		int index = buf->coda;
		buf->coda = (buf->coda +1)%DIM_BUF;
		signal_sem(ds_sem,SPAZIO_DISP,1);
		printf("[CONS %d]: messaggio letto in posizione %d: %d\n",getpid(),index,buf->elem[index]);

	
	}


	return 0;
}
