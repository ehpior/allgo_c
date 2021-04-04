#include <stdio.h>
#include <mysql.h>
#include <errno.h>

void main(void)
{ 
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

    if(mysql_query(&mysql, "USE allgo") )
    // mysql_query()는 query 수행시에 에러가 나게 되면
    // 0이 아닌 값을 리턴한다.
    {
        printf("%s\n", mysql_error(&mysql));
        exit(1) ;
    }

    memset(query, 0x00, 255);

    sprintf(query, "insert into allgo1(date, code, score) values('%.6s','%.6s','%lf')", "20210322", code, score);
    if(mysql_query(&mysql, query) )
    {
        printf("%s\n", mysql_error(&mysql)) ;
        exit(1);
    }
    
    mysql_close(&mysql);
}
