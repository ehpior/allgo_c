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

#include "common.h"

#define BLOCK      255
#define FILENAME "buf.txt"
#define REAL_CHEG_DIR "data/real_cheg/"
#define REAL_PROGRAM_DIR "data/real_program/"
#define BUFFSIZE 73

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
    
    //소켓 생성
    if((s = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket fail");
        exit(0);
    }
    
    // 서버 구조
    memset(&cliaddr, 0, addrlen); //bzero((char *)&cliaddr, addrlen);
    memset(&servaddr, 0, addrlen); //bzero((char *)&servaddr,addrlen);
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(atoi(argv[1])); //argv[1]에서 port 번호 가지고 옴

    // 서버 로컬 주소로 bind()
    if(bind(s, (struct sockaddr *)&servaddr, addrlen) < 0) {
        perror("bind fail");
        exit(0);
    }

    real_program_data *cur_program_data = (real_program_data*) shm_get(REAL_PROGRAM_SHM, sizeof(real_program_data), 0);

    if(cur_program_data == NULL){
        printf("error??\n");
        exit(1);
    }
    
    //저장용 파일 생성
	
    while(1)
    {
        puts("Server : waiting request.");
        memset(buf, 0x00, BUFFSIZE);
         //전송 받은 메시지 nbyte 저장
        nbyte = recvfrom(s, buf, BUFFSIZE , 0, (struct sockaddr *)&cliaddr, &addrlen);
        if(nbyte< 0) {
            perror("recvfrom fail");
            exit(1);
        }
        //buf[nbyte] = 0; //마지막 값에 0
	
        printf("%d byte recv\n",nbyte);

        real_program *p = (real_program*) buf;

        //memcpy(cur_cheg, buf, BUFFSIZE);
        int index = p->index;

        printf("[%.6s, %.6s, %d, %d, %d]\n", p->code, p->time, p->price, p->change_price, p->increase_rate);
        //printf("[%.6s, %.6s, %d, %d, %d]\n", cur_cheg->code, cur_cheg->time, cur_cheg->price, cur_cheg->change_price, cur_cheg->increase_rate);

        memcpy(&cur_program_data->data[index], buf, BUFFSIZE);

        printf("[%.6s, %.6s, %d, %d, %d]\n", cur_program_data->data[index].code, cur_program_data->data[index].time, 
            cur_program_data->data[index].price, cur_program_data->data[index].change_price, cur_program_data->data[index].increase_rate);

        memset(file_dir, 0x00, sizeof(file_dir));
        sprintf(file_dir, "%s%.6s", REAL_PROGRAM_DIR, p->code);

        if((stream = fopen(file_dir, "a")) == 0) {
            printf("Faile open error\n");
            exit(1);
        }

        fprintf(stream, "[%.6s, %.6s, %d, %d, %d]\n", p->code, p->time, p->price, p->change_price, p->increase_rate); //파일로 저장
        fflush(stream);
        fclose(stream);

        puts("sendto complete");
    }

	/*while(!feof(stream)) {
		buf[0] = '\0';
		fgets(buf, BLOCK, stream);
		printf("Send : %s\n", buf);
        //메시지 전송
		if(sendto(s, buf, strlen(buf), 0, (struct sockaddr *)&cliaddr, addrlen) < 0) {
			perror("sendto fail");
			exit(0);
		}
	}*/
	fclose(stream);
    close(s);
	return 0;
}