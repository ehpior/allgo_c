#include <stdio.h>
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


    real_program_data *data = (real_program_data*) shm_get(REAL_PROGRAM_SHM, sizeof(real_program_data), SHM_READ);
    
    if(data == NULL){
        printf("[error]shm_get\n");
        exit(1);
    }
    printf("[success]SHM_ACCESS\n");


    mysql_init(&mysql);

    if(!mysql_real_connect(&mysql, NULL, "jhk","wjdgusrl34", NULL ,3306, (char *)NULL, 0))
    {
        printf("[error]%s\n",mysql_error(&mysql));
        exit(1);
    }
    printf("[success]DB_ACCESS\n");


    if(mysql_query(&mysql, "USE allgo") )
    // mysql_query()는 query 수행시에 에러가 나게 되면
    // 0이 아닌 값을 리턴한다.
    {
        printf("[error]%s\n", mysql_error(&mysql));
        exit(1);
    }

    int i=0;

    for(i=0; i<3000; i++){

        real_program program = data->data[i];

        if(program.price <= 0){
            continue;
        }

        memset(query, 0x00, 9192);

        sprintf(query, "insert into STOCK_CHEG(date, code, sell_volume, \
                    sell_amount, buy_volume, buy_amount, net_buy_volume, \
                    net_buy_amount, market, ticker)\
                values('%.8s','%.6s', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f')",\
                    today, program.code, program.sell_volume, \
                    program.sell_amount, program.nuy_volume, program.buy_amount, program.net_buy_volume, \
                    program.net_buy_amount, program.markget, program.ticker);

        if(mysql_query(&mysql, query) )
        {
            printf("%s\n", mysql_error(&mysql));
            exit(1);
        }
    }
    

    printf("[success]end\n");
    mysql_close(&mysql);
    exit(0);
}
