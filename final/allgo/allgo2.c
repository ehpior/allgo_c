#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <mysql.h>

#include "../common.h"

int main(int argc, char *argv[]){

    MYSQL mysql;
    MYSQL_RES* res;
    MYSQL_ROW row;
    int fields;
    int cnt;
    char query[1024];

    char today[9];
    memset(today, 0x00, 9);
    sprintf(today, "%.8s", argv[1]);

    printf("[success]today is %.8s\n", today);


    real_program_data *program_data = (real_program_data*) shm_get(REAL_PROGRAM_SHM, sizeof(real_program_data), SHM_READ);
    real_cheg_data *cheg_data = (real_cheg_data*) shm_get(REAL_CHEG_SHM, sizeof(real_cheg_data), SHM_READ);

    if(program_data == NULL){
        printf("[error]shm_get\n");
        exit(1);
    }
    printf("[success]SHM_ACCESS\n");


    mysql_init(&mysql);

    if(!mysql_real_connect(&mysql, NULL, "jhk","wjdgusrl34", NULL ,3306, (char *)NULL, 0)){
        printf("[error]%s\n",mysql_error(&mysql));
        exit(1);
    }
    printf("[success]DB_ACCESS\n");


    if(mysql_query(&mysql, "USE allgo")){
        printf("[error]%s\n", mysql_error(&mysql));
        exit(1);
    }

    int i = 0;

    for(i=0 ; i<5000 ; i++){
        memset(query, 0x00, 1024);
        
        real_program program = program_data->data[i];

        if(program.sell_volume <= 0){
            continue;
        }

        float score = program.net_buy_amount / cheg_data->data[i].capitalization;

        sprintf(query, "insert into ag_score(date, type, code, score) values('%.8s','B','%.6s','%.2f')", 
            today, cheg_data->data[i].code, score);

        if(mysql_query(&mysql, query))
        {
            printf("[error]%s\n", mysql_error(&mysql));
            mysql_close(&mysql);
            exit(1);
        }

        //printf("%d : %lf\n", i, final_score[i]);
    }

    printf("[success]end\n");
    mysql_close(&mysql);
    exit(0);
}

