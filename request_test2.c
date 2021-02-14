#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>    //write

#include <stdio.h>
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
    int BUFFSIZE = 40;
    char buff[BUFFSIZE];
    int ssock, csock;
    int nread;
    struct sockaddr_in client;
    int clilen = sizeof(client);
    setlocale(LC_ALL, "KOREAN");

    ssock = clientSocket(PORT);
    printf("connect finish %d\n", PORT);
    fflush(stdout);

    int i=0;
    char testhk[10];
    scanf("%s",testhk);
    printf("%s\n",testhk);
    fflush(stdout);

    printf("accepted & send\n");
    fflush(stdout);
    sendMsg(ssock, testhk, strlen(testhk));

    int cnt=0;
   
    //printf("Accepted connection from %s\n", inet_ntoa(client.sin_addr));
    memset(buff, 0x00, BUFFSIZE);

    nread=read(ssock, buff, BUFFSIZE);

    if(nread > 0){

        opt10081 *p = (opt10081*) buff;
        printf("Received contents: [%.8s, %d, %d, %d, %.8s, %d, %d, %d]\n",
                p->code, p->price, p->volume, p->amount, p->date, p->open, p->high, p->low);
        fflush(stdout);
    }

    closeSocket(csock);
    closeSocket(ssock);
    printf("bye");
    fflush(stdout);
    return 0;
}