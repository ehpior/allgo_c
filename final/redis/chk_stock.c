#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#include "hiredis.h"
 
int main(void) {
    unsigned int j;
    redisContext *c;
    redisReply *reply;
 
    struct timeval timeout = { 1, 500000 }; // 1.5 seconds
    c = redisConnectWithTimeout((char*)"127.0.0.1", 6379, timeout);
    if (c->err) {
        printf("Connection error: %s\n", c->errstr);
        exit(1);
    }

    /* PING server */
    reply = redisCommand(c,"AUTH wjdgusrl34");
    printf("AUTH: %s\n", reply->str);
    freeReplyObject(reply);
 
    /* PING server */
    reply = redisCommand(c,"PING");
    printf("PING: %s\n", reply->str);
    freeReplyObject(reply);
 
    /* Try a GET and two INCR */
    reply = redisCommand(c,"GET stock:005930");
    printf("GET: %s\n", reply->str);
    freeReplyObject(reply);
 
    return 0;
}
