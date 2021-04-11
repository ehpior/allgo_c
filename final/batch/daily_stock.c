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


    real_cheg_data *data = (real_cheg_data*) shm_get(REAL_CHEG_SHM, sizeof(real_cheg_data), SHM_READ);

    if(data == NULL){
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
                    today, cheg.code, cheg.price, cheg.change_price, \
                    cheg.increase_rate, cheg.cul_volume, cheg.cul_amount, cheg.open, cheg.high, cheg.low, cheg.turn_over, cheg.volume_power,\
                    cheg.capitalization, cheg.market, cheg.high_time, cheg.low_time);

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

int main(void)
{
	MYSQL *cons = mysql_init(NULL);
	MYSQL_RES *sql_result;
	MYSQL_ROW sql_row; // = char **sql_row; 2차원 배열 = 1차원 문자열 배열
	loadmysql(MYSQLIP, cons);
	mysql_query(cons, "select * from test.test");
	sql_result = mysql_store_result(cons);
	while (sql_row = mysql_fetch_row(sql_result)) { //값이 없을때까지 변환함
		printf("%s %s %s\n", sql_row[0], sql_row[1], sql_row[2]);
	}
    mysql_free_result(sql_result);
	getchar();
	return 0;
}
