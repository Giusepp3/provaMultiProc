#include "header.h"

void wait_sem(int id_sem, int numsem,int n){
	struct sembuf sem_buf;
	sem_buf.sem_num = numsem;
	sem_buf.sem_op = -n;
	sem_buf.sem_flg = 0;
	semop(id_sem,&sem_buf,1);
}

void signal_sem(int id_sem, int numsem, int n){
	struct sembuf sem_buf;
	sem_buf.sem_num = numsem;
	sem_buf.sem_op = n;
	sem_buf.sem_flg = 0;
	semop(id_sem,&sem_buf,1);
}



