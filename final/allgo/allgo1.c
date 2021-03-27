#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <mysql.h>

#include "../common.h"

void main(){

    MYSQL mysql;
    MYSQL_RES* res;
    MYSQL_ROW row;
    int fields;
    int cnt;
    char query[255];

    mysql_init(&mysql);

    if(!mysql_real_connect(&mysql, NULL, "jhk","wjdgusrl34", NULL ,3306, (char *)NULL, 0))
    {
        printf("%s\n",mysql_error(&mysql));
        exit(1);
    }
    printf("success\n");





    real_cheg_data *cur_cheg_data = (real_cheg_data*)shm_get(REAL_CHEG_SHM, sizeof(real_cheg_data), SHM_READ);

    if(cur_cheg_data == NULL){
        return;
    }

    double final_score[3000] = {0.0,};

    int i = 0;

    for(i=0 ; i<3000 ; i++){
        if(cur_cheg_data->data[i].price <= 0){
            continue;
        }
        int vp = cur_cheg_data->data[i].volume_power;
        int inc_rate = cur_cheg_data->data[i].increase_rate;
        int change_price = cur_cheg_data->data[i].change_price;
        int open = cur_cheg_data->data[i].open;
        int close = cur_cheg_data->data[i].price;
        int high = cur_cheg_data->data[i].high;
        int low = cur_cheg_data->data[i].low;

        double day_score = 0.0;
        
        if(vp < 20 && vp >0){
            vp = 20;
        }else if(vp <= 450 && vp > 180){
            vp = 180;
        }
        
        double vari = (vp + 20) / 40.0;
            
        if(inc_rate < 0){
            day_score = (-1/(22-2*vari))*pow(inc_rate+1-vari,2) + 1-0.5*vari;
        } else if(0 <= inc_rate && inc_rate < 4){
            day_score = (-1/(9+vari))*pow(inc_rate-3, 2) + 1 +abs(-5 + 1.5*vari);
        } else{
            day_score = (-1/(16-vari))*pow(inc_rate-3, 2) + 1 +abs(-5 + 1.5*vari);
        }  
            
        if(vp > 450 || vp < 15){
            day_score = -10;
        }
        
        if(inc_rate >= 0 && change_price < 0){
            day_score = day_score *0.5;
        }
            
        //if inc_rate < 0 and  change_price > 0:
        //     day_score = day_score *0.5
        
        if(high != low){
            day_score = day_score * 0.5 * pow(1.5, abs((close - open) / (high - low)));
        }
        else{
            day_score = day_score * 0.5;
        }

        final_score[i] = day_score;
    }



    if(mysql_query(&mysql, "USE allgo") )
    // mysql_query()는 query 수행시에 에러가 나게 되면
    // 0이 아닌 값을 리턴한다.
    {
        printf("%s\n", mysql_error(&mysql));
        exit(1) ;
    }

    for(i=0 ; i<3000 ; i++){
        if(cur_cheg_data->data[i].price <= 0){
            continue;
        }

        memset(query, 0x00, 255);

        sprintf(query, "insert into allgo1(date, code, score) values('%.8s','%.6s','%lf')", 
            "20210322", cur_cheg_data->data[i].code, final_score[i]);

        if(mysql_query(&mysql, query))
        {
            printf("%s\n", mysql_error(&mysql));
            mysql_close(&mysql);
            exit(1);
        }

        //printf("%d : %lf\n", i, final_score[i]);
    }

    mysql_close(&mysql);
}

