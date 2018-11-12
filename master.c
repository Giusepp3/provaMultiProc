#include "header.h"

int main(){
	printf("[MASTER %d]: inizio il programma\n",getpid());
	key_t shm_key = ftok(FTOK_PATH,FTOK_CHAR);
	int ds_shm = shmget(shm_key,sizeof(int),IPC_CREAT | PERM);
	buffer_circ* buf = (buffer_circ*) shmat(ds_shm,NULL,0);
	printf("[MASTER %d]: memoria condivisa creata\n",getpid());
	key_t sem_key = ftok(FTOK_PATH,FTOK_CHAR);
	int ds_sem = semget(sem_key,N_SEMS,IPC_CREAT | PERM);
	semctl(ds_sem,SETVAL,SPAZIO_DISP);
	int a = SPAZIO_DISP;
	printf("[MASTER %d]: semaforo creato e inizializzato a %d\n",getpid(),a);
	int pid = fork();
	if(!pid){
		execl("./prod",NULL);
		perror("errore nella execl di prod.o\n");
		_exit(-3);
	}
	pid = fork();
	if(!pid){
		execl("./cons",NULL);
		perror("errore nella execl di cons.o\n");
		_exit(-4);
	}

	wait();
	wait();

	shmctl(ds_shm,IPC_RMID,0);
	printf("[MASTER %d]: memoria condivisa rimossa\n",getpid());
	semctl(ds_sem,0,IPC_RMID);
	printf("[MASTER %d]: semaforo rimosso\n",getpid());
	

	printf("[MASTER %d]: programma terminato\n",getpid());

	return 0;
}
