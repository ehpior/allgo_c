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
    if(mysql_query(&mysql, "SELECT * FROM admin") )
    {
        printf("%s\n", mysql_error(&mysql)) ;
        exit(1);
    }

    res = mysql_store_result(&mysql);
    fields = mysql_num_fields(res);

    while( ( row = mysql_fetch_row( res ) ))
    {
        for( cnt = 0 ; cnt < fields ; ++cnt)
            printf("%12s ", row[cnt]);

        printf("\n") ;
    }
    mysql_free_result(res);
    mysql_close(&mysql);
}
