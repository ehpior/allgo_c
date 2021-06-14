#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql.h>
#include <errno.h>
#include <sys/shm.h>

#include "../common.h"

int main(int argc, char* argv[])
{ 
    MYSQL mysql;
    MYSQL_RES* res;
    MYSQL_ROW row;
    int fields;
    int cnt;
    char query[9192];

    if(argc == 1){
        printf("[error]input error\n");
        exit(1);
    }

    char today[8+1];
    memset(today, 0x00, 9);
    sprintf(today, "%.8s", argv[1]);

    printf("[success]today is %.8s\n", today);

    mysql_init(&mysql);

    if(!mysql_real_connect(&mysql, NULL, "jhk","wjdgusrl34", NULL ,3306, (char *)NULL, 0))
    {
        printf("%s\n",mysql_error(&mysql));
        return 1;
    }
    printf("DB_ACCESS success\n");

    real_program_data *data = (real_program_data*) shm_get(REAL_PROGRAM_SHM, sizeof(real_program_data), SHM_READ);

    if(data == NULL){
        return 1;
    }
    printf("SHM_ACCESS success\n");

    if(mysql_query(&mysql, "USE allgo") ){
        printf("%s\n", mysql_error(&mysql));
        return 1;
    }

    int i=0;

    for(i=0; i<5000; i++){

        real_program program = data->data[i];

        if(program.sell_volume <= 0){
            continue;
        }

        memset(query, 0x00, 9192);

	sprintf(query, "insert into stock_program(date, code, sell_volume, \
                    sell_amount, buy_volume, buy_amount, net_buy_volume, \
                    net_buy_amount, market, ticker)\
                values('%.8s','%.6s', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f')",\
                    today, program.code, program.sell_volume, \
                    program.sell_amount, program.buy_volume, program.buy_amount, program.net_buy_volume, \
                    program.net_buy_amount, program.market, program.ticker);

        if(mysql_query(&mysql, query) )
        {
            printf("%s\n", mysql_error(&mysql));
            //return 1;
        }
    }

    printf("[success]end\n");    
    mysql_close(&mysql);
    return 0;

}
