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

	char code[8];	// 0.종목코드8
	int price;		// 1.현재가4
	int volume;		// 2.거래량4
	int amount;		// 3.거래대금4
	char date[8];	// 4.일자8
	int open;		// 5.시가4
	int high;		// 6.고가4
	int low;		// 7.저가4
	int a1;			// 8.수정주가구분
	int a2;			// 9.수정비율
	int a3;			// 10.대업종구분
	int a4;			// 11.소업종구분
	int a5;			// 12.종목정보
	int a6;			// 13.수정주가이벤트
	int a7;			// 14.전일종가
	
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

    ssock = createSocket(PORT);
    printf("Server listening on port %d\n", PORT);
    csock = accept(ssock, (struct sockaddr *)&client, &clilen);
    if (csock < 0)
    {
        printf("Error: accept() failed\n");
        return 0;
    }
    int i=0;

    char testhk[10];
    printf("scanning\n");
    scanf("%s",testhk);

    sendMsg(csock, testhk, strlen(testhk));

    int cnt=0;

    while (1)
    {    
        printf("Accepted connection from %s\n", inet_ntoa(client.sin_addr));
        //bzero(buff, BUFFSIZE);
        memset(buff, 0x00, BUFFSIZE);

        while ((nread=read(csock, buff, BUFFSIZE)) > 0)
        {
            //printf("\nReceived %d bytes\n", nread);
            //payload *p = (payload*) buff;
            //printf("Received contents: [%d, %.8s, %d, %d, %d, %d, %d, %d]\n",
            //        p->idx, p->code, p->vol, p->amt, p->date, p->open, p->high, p->low);

            opt10081 *p = (opt10081*) buff;
            printf("Received contents: [%.8s, %d, %d, %d, %.8s, %d, %d, %d]\n",
                    p->code, p->price, p->volume, p->amount, p->date, p->open, p->high, p->low);
            
            if(cnt >= 2){
                closeSocket(csock);
                closeSocket(ssock);
                return 0;
            }
            //printf("Sending it back.. ");
            //sendMsg(csock, p, sizeof(payload));
            memset(buff, 0x00, BUFFSIZE);
            cnt++;
        }
        //printf("Closing connection to client\n");
        //printf("----------------------------\n");
        //closeSocket(csock); 
    }

    closeSocket(ssock);
    printf("bye");
    return 0;
}