#include <stdio.h>
#include <mysql.h>
#include <errno.h>
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

void main(int argc, char *argv[])
{ 
    MYSQL mysql;
    MYSQL_RES* res;
    MYSQL_ROW row;
    int fields;
    int cnt;
    char query[4096];

    char today[8];
    memset(today, 0x00, 8);
    sprintf(today, "%.8s", argv[1]);

    printf("today is %.8s\n", today);

    mysql_init(&mysql);

    if(!mysql_real_connect(&mysql, NULL, "jhk","wjdgusrl34", NULL ,3306, (char *)NULL, 0))
    {
        printf("%s\n",mysql_error(&mysql));
        exit(1);
    }
    printf("DB_ACCESS success\n");

    real_cheg_data *data = (real_cheg_data*) shm_get(REAL_CHEG_SHM, sizeof(real_cheg_data), SHM_READ);

    if(data == NULL){
        return;
    }
    printf("SHM_ACCESS success")

    if(mysql_query(&mysql, "USE allgo") )
    // mysql_query()는 query 수행시에 에러가 나게 되면
    // 0이 아닌 값을 리턴한다.
    {
        printf("%s\n", mysql_error(&mysql));
        exit(1) ;
    }


    int i=0;

    for(i=0; i<3000; i++){

        real_cheg cheg = data->data[i];

        if(cheg.price <= 0){
            continue;
        }

        memset(query, 0x00, 4096);

        sprintf(query, "insert into STOCK_CHEG(date, code, price, change_price, 
                    increase_rate, cul_volume, cul_amount, open, high, low, turn_over, volume_power, 
                    capitalization, market, high_time, low_time)
                values('%.8s','%.6s', '%lf', '%lf', '%lf', '%lf', '%lf', '%lf', '%lf', '%lf', '%lf', '%lf', '%lf', '%lf', '%lf', '%lf')",
                    today, cheg.code, cheg.price, cheg.change_price, 
                    cheg.increase_rate, cheg.cul_volume, cheg.cul_amount, cheg.open, cheg.high, cheg.low, cheg.turn_over, cheg.volume_power,
                    cheg.capitalization, cheg.market, cheg.high_time, cheg.low_time);

        if(mysql_query(&mysql, query) )
        {
            printf("%s\n", mysql_error(&mysql)) ;
            exit(1);
        }
    }
    
    
    
    mysql_close(&mysql);
}
