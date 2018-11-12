#include "header.h"

int main(void){
	buffer_circ* buf;
	key_t shm_key = ftok(FTOK_PATH,FTOK_CHAR);
	int ds_shm = shmget(shm_key,sizeof(int), IPC_CREAT | 0664);
	printf("[PROD %d]: creato descrittore per la memoria condivisa\n",getpid());

	if(ds_shm<0){
		 char * err = NULL;
                strcat(err,"[PROD ");
                char * pid = NULL;
                *pid = (char)getpid();
                strcat(err,pid);
                strcat(err,"]: errore shm\n");
                perror(err);
                _exit(-1);

	}

	buf = (buffer_circ*) shmat(ds_shm,NULL,0);

	key_t sem_key = ftok(FTOK_PATH,FTOK_CHAR);
	printf("[PROD %d]: creata la chiave per il semaforo\n",getpid());
	int ds_sem = semget(sem_key,N_SEMS,IPC_CREAT | 0664);
	printf("[PROD %d]: creato il descrittore per il semaforo\n",getpid());
	

	for(int i = 0; i<N_MESS;i++){
		srand(time(NULL));
		int mess = rand()%200;
		wait_sem(ds_sem,SPAZIO_DISP,1);
		int index = buf->testa;
		buf->testa = (buf->testa +1)%DIM_BUF;
		signal_sem(ds_sem,MESS_DISP,1);
		buf->elem[index] = mess;
		printf("[PROD %d]: inserito messaggio %d nel buffer in posizione %d\n",getpid(),mess,index);

	}
		
		
	return 0;
}
