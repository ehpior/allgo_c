#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql.h>
#include <errno.h>
#include <sys/shm.h>

#include "../common.h"

void main(int argc, char* argv[])
{ 
    MYSQL mysql;
    MYSQL_RES* res;
    MYSQL_ROW row;
    int fields;
    int cnt;
    char query[4096];

    char today[8+1];
    memset(today, 0x00, 9);
    sprintf(today, "%.8s", argv[1]);

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
    printf("SHM_ACCESS success");

    if(mysql_query(&mysql, "USE allgo") )
    // mysql_query()는 query 수행시에 에러가 나게 되면
    // 0이 아닌 값을 리턴한다.
    {
        printf("%s\n", mysql_error(&mysql));
        exit(1);
    }


    int i=0;

    for(i=0; i<3000; i++){

        real_cheg cheg = data->data[i];

        if(cheg.price <= 0){
            continue;
        }

        memset(query, 0x00, 9192);

        sprintf(query, "insert into STOCK_CHEG(date, code, price, change_price, \
                    increase_rate, cul_volume, cul_amount, open, high, low, turn_over, volume_power, \
                    capitalization, market, high_time, low_time)\
                values('%.8s','%.6s', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f')",\
                    "20210405", cheg.code, cheg.price, cheg.change_price, \
                    cheg.increase_rate, cheg.cul_volume, cheg.cul_amount, cheg.open, cheg.high, cheg.low, cheg.turn_over, cheg.volume_power,\
                    cheg.capitalization, cheg.market, cheg.high_time, cheg.low_time);

        if(mysql_query(&mysql, query) )
        {
            printf("%s\n", mysql_error(&mysql));
            exit(1);
        }
    }
    
    
    
    mysql_close(&mysql);
}
