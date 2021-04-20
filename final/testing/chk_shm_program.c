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

    real_program_data *data = (real_program_data*) shm_get(REAL_PROGRAM_SHM, sizeof(real_program_data), SHM_READ);

    if(data == NULL){
        printf("shm_data NULL\n");
        return;
    }

    char code[7];
    memset(code, 0x00, 7);

	memcpy(code, argv[1], 6);

	int index=0;

	for(index=0 ; index<5000 ; index++){
		if(!strncmp(code, data->data[index].code, 6)){
			printf("\nindex \t\t: %d\ncode \t\t: %.6s\ntime \t\t: %.6s\nprice \t\t: %f\nplus_minus \t: %f\nchange_price \t: %f\n\
increase_rate \t: %f\ncul_volume \t: %f\nsell_volume \t: %f\nsell_amount \t: %f\nbuy_volume \t: %f\n\
buy_amount \t: %f\nnet_buy_volume \t: %f\nnet_buy_amount \t: %f\na1 \t\t: %f\na2 \t\t: %f\nmarket \t\t: %f\nticker \t\t: %f\n\n", 
				data->data[index].index, data->data[index].code, data->data[index].time,
                data->data[index].price, data->data[index].plus_minus, data->data[index].change_price, 
				data->data[index].increase_rate, data->data[index].cul_volume, data->data[index].sell_volume, 
				data->data[index].sell_amount, data->data[index].buy_volume, data->data[index].buy_amount, 
				data->data[index].net_buy_volume, data->data[index].net_buy_amount, data->data[index].a1, 
				data->data[index].a2, data->data[index].market, data->data[index].ticker);
            break;
            }
    }
}
