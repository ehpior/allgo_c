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

	real_cheg_data *cur_cheg_data = (real_cheg_data*) shm_get(REAL_CHEG_SHM, sizeof(real_cheg_data), SHM_READWRITE);

    if(cur_cheg_data == NULL){
		printf("cheg null\n");
        return;
    }

    for(int i=0 ; i<5000; i++){
        memset(&cur_cheg_data->data[i], 0x00, sizeof(real_cheg));
    }

	real_program_data *cur_program_data = (real_program_data*) shm_get(REAL_PROGRAM_SHM, sizeof(real_cheg_data), SHM_READWRITE);

    if(cur_program_data == NULL){
		printf("program null\n");
        return;
    }

    for(int i=0 ; i<5000; i++){
        memset(&cur_program_data->data[i], 0x00, sizeof(real_program));
    } 

}