#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>    //write
#include <sys/shm.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <wchar.h>

#include "real_cheg.h"
#include "real_program.h"

char *shm_data = NULL;

/* 0 = read/write, 1 = read */
char *shm_get(key_t key, int size, int mode){

    int shmid = shmget((key_t)key, size, 0666|IPC_CREAT);
	if( shmid == -1 ) {
		return (NULL);
	}

    char *shmadd = shmat(shmid, (char *)0, mode);
	if( shmadd == (char *)-1 ) {
		return (NULL);
	}

	shm_data = (char *)shmadd;

	return shm_data;
}

int createSocket(int port)
{
    int sock, err;
    struct sockaddr_in server;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("ERROR: Socket creation failed\n");
        exit(1);
    }
    printf("Socket created\n");

    bzero((char *) &server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);
    if (bind(sock, (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        printf("ERROR: Bind failed\n");
        exit(1);
    }
    printf("Bind done\n");

    listen(sock , 3);

    return sock;
}

int clientSocket(int port)
{
    int sock, err;
    struct sockaddr_in server;

    printf("before socket()\n");
    fflush(stdout);
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("ERROR: Socket creation failed\n");
        exit(1);
    }
    printf("Socket created\n");
    fflush(stdout);

    bzero((char *) &server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("192.168.0.26");
    server.sin_port = htons(port);

    if(connect(sock, (struct sockaddr*)&server, sizeof(server)) == -1){
        printf("ERROR: Socket creation failed\n");
        exit(1);
    }
    printf("Socket created\n");
    fflush(stdout);

    return sock;
}

void closeSocket(int sock)
{
    close(sock);
    return;
}

void sendMsg(int sock, void* msg, uint32_t msgsize)
{
    if (write(sock, msg, msgsize) < 0)
    {
        printf("Can't send message.\n");
        closeSocket(sock);
        exit(1);
    }
    printf("Message sent (%d bytes).\n", msgsize);
    return;
}

int main()
{
    int PORT = 8888;
    int BUFFSIZE = 105;
    char buff[BUFFSIZE];
    char index[4];
    int ssock, csock;
    int nread;
    struct sockaddr_in client;
    int clilen = sizeof(client);
    setlocale(LC_ALL, "KOREAN");

    ssock = clientSocket(PORT);
    printf("connect finish %d\n", PORT);

    printf("Accepted connection from %s\n", inet_ntoa(client.sin_addr));

    real_cheg *cur_cheg = (real_cheg*) shm_get(9999, 101, 0);

    while (1)
    {    
        memset(buff, 0x00, BUFFSIZE);
        memset(index, 0x00, 4);

        //while ((read(ssock, index, 4)) > 0)
        while ((read(ssock, buff, BUFFSIZE)) > 0)
        {
            //printf("%d ", *((int*)index));
            //nread = read(ssock, buff, BUFFSIZE);
            real_cheg *p = (real_cheg*) buff;
            memcpy(cur_cheg, buff, BUFFSIZE);
            /*printf("Received contents: [%.8s, %d, %d, %d, %.8s, %d, %d, %d]\n",
                    p->code, p->price, p->volume, p->amount, p->date, p->open, p->high, p->low);*/

            printf("[%.6s, %.6s, %d, %d, %d]\n", p->code, p->time, p->price, p->change_price, p->increase_rate);
            printf("[%.6s, %.6s, %d, %d, %d]\n", cur_cheg->code, cur_cheg->time, cur_cheg->price, cur_cheg->change_price, cur_cheg->increase_rate);

            memset(buff, 0x00, BUFFSIZE);
        }
        printf("sleep\n");
        sleep(1);
    }

    closeSocket(ssock);
    printf("bye");
    return 0;
}