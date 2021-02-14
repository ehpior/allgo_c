#include "com_allgo_web_jni_TestJni.h"
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>    //write
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <wchar.h>

#pragma pack(1)

typedef struct opt10081{

	char code[8];	// 0.�����ڵ�8
	int price;		// 1.���簡4
	int volume;		// 2.�ŷ���4
	int amount;		// 3.�ŷ����4
	char date[8];	// 4.����8
	int open;		// 5.�ð�4
	int high;		// 6.��4
	int low;		// 7.����4
	int a1;			// 8.�����ְ�����
	int a2;			// 9.��������
	int a3;			// 10.���������
	int a4;			// 11.�Ҿ�������
	int a5;			// 12.��������
	int a6;			// 13.�����ְ��̺�Ʈ
	int a7;			// 14.��������
	
} opt10081;

typedef struct payload_t {
    uint32_t idx;
    char code[8];
    uint32_t vol;
    uint32_t amt;
    uint32_t date;
    uint32_t open;
    uint32_t high;
    uint32_t low;
} payload;

#pragma pack()

void connect_alarm(int signo){
    printf("alarm\n");
    fflush(stdout);
    return;
}

int createSocket(int port)
{
    int sock, err;
    struct sockaddr_in server;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("ERROR: Socket creation failed\n");
        return -1;
    }
    printf("Socket created\n");

    bzero((char *) &server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);
    if (bind(sock, (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        printf("ERROR: Bind failed\n");
        return -1;
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
        return -1;
    }
    printf("Socket created\n");
    fflush(stdout);

    bzero((char *) &server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("192.168.0.26");
    server.sin_port = htons(port);
    signal(SIGALRM, connect_alarm);
    alarm(1);
    if(connect(sock, (struct sockaddr*)&server, sizeof(server)) == -1){
        printf("ERROR: Socket creation failed\n");
        fflush(stdout);
        return -1;
    }
    alarm(0);
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
        return;
    }
    printf("Message sent (%d bytes).\n", msgsize);
    return;
}

JNIEXPORT void JNICALL Java_com_allgo_web_jni_TestJni_printHello(JNIEnv *env, jobject obj)
{
    printf("Hello World\n");
    fflush(stdout);
}

JNIEXPORT void JNICALL Java_com_allgo_web_jni_TestJni_printString(JNIEnv *env, jobject obj, jstring string)
{

    const char *str = (*env)->GetStringUTFChars(env, string, 0); 

    int PORT = 8888;
    int BUFFSIZE = 40;
    char buff[BUFFSIZE];
    int ssock, csock;
    int nread;
    struct sockaddr_in client;
    int clilen = sizeof(client);
    setlocale(LC_ALL, "KOREAN");

    ssock = clientSocket(PORT);
    if(ssock < 0){
        return;
    }
    printf("connect finish %d\n", PORT);
    fflush(stdout);

    int i=0;
    char testhk[10];
    printf("%s\n",str);
    fflush(stdout);
    sprintf(testhk, "%s",str);
    printf("%s\n",testhk);
    fflush(stdout);

    printf("accepted & send\n");
    fflush(stdout);
    sendMsg(ssock, testhk, strlen(testhk));

    int cnt=0;
   
    printf("Accepted connection from %s\n", inet_ntoa(client.sin_addr));
    fflush(stdout);
    memset(buff, 0x00, BUFFSIZE);

    nread=read(ssock, buff, BUFFSIZE);

    if(nread > 0){

        opt10081 *p = (opt10081*) buff;
        printf("Received contents: [%.8s, %d, %d, %d, %.8s, %d, %d, %d]\n",
                p->code, p->price, p->volume, p->amount, p->date, p->open, p->high, p->low);
        fflush(stdout);
    }

    closeSocket(ssock);
    printf("bye");
    fflush(stdout);
    return;
}