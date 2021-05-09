//--------------------------------------------------------------
// file Name : udp_echoserv.c
// command : cc -o udp_echoserv  udp_echoserv.c
// server 시작 : udp_echoserv  9999
// client에서 전송되는 메시지를 buf.txt 에 저장하고, 다시 client로 전송 후 유효성 체크
//--------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <mysql.h>
#include <errno.h>

#include "hiredis.h"
#include "common.h"

#define BLOCK      255
#define FILENAME "buf.txt"
#define REAL_CHEG_DIR "/Users/jhk/hk/final/data/real_cheg/"
#define REAL_PROGRAM_DIR "/Users/jhk/hk/final/data/real_program/"
#define BUFFSIZE 106

int main(int argc, char *argv[]) {
    struct sockaddr_in servaddr, cliaddr;
    int s, nbyte, addrlen = sizeof(struct sockaddr);
    char buf[BUFFSIZE+1];
    char file_dir[50];
    FILE *stream; //파일 입출력
    
    //파일명 포트번호
    if(argc != 2) { 
        printf("usage: %s port\n", argv[0]);
        exit(0);
    }


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


    
    if((s = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket fail");
        exit(0);
    }
    
    memset(&cliaddr, 0, addrlen); //bzero((char *)&cliaddr, addrlen);
    memset(&servaddr, 0, addrlen); //bzero((char *)&servaddr,addrlen);
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(atoi(argv[1]));

    if(bind(s, (struct sockaddr *)&servaddr, addrlen) < 0) {
        perror("bind fail");
        exit(0);
    }

    real_cheg_data *cur_cheg_data = (real_cheg_data*) shm_get(REAL_CHEG_SHM, sizeof(real_cheg_data), 0);

    if(cur_cheg_data == NULL){
        printf("error??\n");
        exit(1);
    }
    
    char redis_key[20];
    char redis_value[20];
    while(1)
    {
        puts("Server : waiting request.");
        memset(buf, 0x00, BUFFSIZE);
        nbyte = recvfrom(s, buf, BUFFSIZE , 0, (struct sockaddr *)&cliaddr, &addrlen);
        if(nbyte< 0) {
            perror("recvfrom fail");
            exit(1);
        }
	
        printf("%d byte recv\n",nbyte);

        real_cheg *p = (real_cheg*) buf;

        int index = p->index;

        //printf("[%.6s, %.6s, %f, %f, %f]\n", p->code, p->time, p->price, p->change_price, p->increase_rate);

        memcpy(&cur_cheg_data->data[index], buf, BUFFSIZE);

        printf("[%.6s, %.6s, %f, %f, %f]\n", cur_cheg_data->data[index].code, cur_cheg_data->data[index].time, 
            cur_cheg_data->data[index].price, cur_cheg_data->data[index].change_price, cur_cheg_data->data[index].increase_rate);


        memset(redis_key, 0x00, 20);
        memset(redis_value, 0x00, 20);
        sprintf(redis_key, "stock:%.6s", p->code);
        sprintf(redis_value, "%f", p->price);

        reply = redisCommand(c,"SET %s %s", redis_key, redis_value);
        //printf("SET: %s\n", reply->str);
        freeReplyObject(reply);

        memset(file_dir, 0x00, sizeof(file_dir));
        sprintf(file_dir, "%s%.6s", REAL_CHEG_DIR, p->code);

        if((stream = fopen(file_dir, "a+")) == NULL) {
            printf("Faile open error\n");
	        printf("%d %s\n", errno, strerror(errno));
            exit(1);
        }

        //fprintf(stream, "[%.6s, %.6s, %f, %f, %f]\n", p->code, p->time, p->price, p->change_price, p->increase_rate); //파일로 저장
        fprintf(stream, "[%.6s, %.6s, %f]\n", p->code, p->time, p->price); //파일로 저장
        fflush(stream);
	    rewind(stream);
        fclose(stream);

        puts("sendto complete");
    }

	fclose(stream);
    close(s);
	return 0;
}
