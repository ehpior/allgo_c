#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>

#include "../common.h"

char *shm_data = NULL;

/* 0 = read/write, 1 = read */
char *shm_get(key_t key, int size, int mode){

    int shmid = shmget((key_t)key, size, 0666|IPC_CREAT);
	if( shmid == -1 ) {
		return (NULL);
	}

    char *shmadd = shmat(shmid, (char *)0, mode);
	if( shmadd == (char *)-1 ) {
		return (NULL);
	}

	shm_data = (char *)shmadd;

	return shm_data;
}

void main(int argc, char *argv[]){

	real_cheg_data *cur_cheg_data = (real_cheg_data*) shm_get(REAL_CHEG_SHM, sizeof(real_cheg_data), SHM_READ);

    if(cur_cheg_data == NULL){
        return;
    }

	int index = atoi(argv[1]);

    printf("[%.6s, %.6s, %d, %d, %d]\n", cur_cheg_data->data[index].code, cur_cheg_data->data[index].time, 
		cur_cheg_data->data[index].price, cur_cheg_data->data[index].change_price, cur_cheg_data->data[index].increase_rate);

}