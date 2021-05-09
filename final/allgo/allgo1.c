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


    real_cheg_data *cheg_data = (real_cheg_data*) shm_get(REAL_CHEG_SHM, sizeof(real_cheg_data), SHM_READ);

    if(cheg_data == NULL){
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


    float final_score[5000] = {0.0,};

    int i = 0;

    for(i=0 ; i<5000 ; i++){
        if(cheg_data->data[i].cul_volume <= 0){
            continue;
        }
        float vp = cheg_data->data[i].volume_power;
        float inc_rate = cheg_data->data[i].increase_rate;
        float change_price = cheg_data->data[i].change_price;
        float open = cheg_data->data[i].open;
        float close = cheg_data->data[i].price;
        float high = cheg_data->data[i].high;
        float low = cheg_data->data[i].low;

        float day_score = 0.0;
        
        if(vp < 20 && vp >0){
            vp = 20;
        }else if(vp <= 450 && vp > 180){
            vp = 180;
        }
        
        float vari = (vp + 20) / 40.0;
            
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


    /*memset(query, 0x00, 1024);
    sprintf(query, "select * from allgo1");

    if(mysql_query(&mysql, query)){   
        printf("[error]%s\n", mysql_error(&mysql));
    }   
  
    res = mysql_store_result(conn);   
  
    while(row = mysql_fetch_row(res))   
    {   
        printf("%s %s\n", row[0], row[1]);   
    }   
    mysql_free_result(res);  */


    /*int a = 1;
    int n = 20;
    float r = 0.9;
    float discount_value = (1-r)/(a*(1-pow(r, n)));

    float weighted_sum = 0.0;
    float weighted_value = 0.0;

    if len(data) < 20:
        continue;
        
    for i in range(n):
        weighted_value = a * (pow(r, i+1)) * discount_value * list_of_day_score[i]; 
        weighted_sum += weighted_value;*/


    for(i=0 ; i<5000 ; i++){
        memset(query, 0x00, 1024);
        
        if(cheg_data->data[i].cul_volume <= 0){
            continue;
        }

        sprintf(query, "insert into AG_SCORE(date, type, code, score) values('%.8s','A','%.6s','%f')", 
            today, cheg_data->data[i].code, final_score[i]);

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

