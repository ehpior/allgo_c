#include <stdio.h>      
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

void main( void)
{
	int   nShmId;
	void *pShmSendBuffer;

	nShmId = shmget((key_t)9999, 1024, IPC_CREAT | 0666);

	if (-1 == nShmId) 
	{
		printf("Shared Memory Create Failed...\n");
		return;
	}

	pShmSendBuffer = shmat(nShmId, NULL, 0);
	if(pShmSendBuffer == (void *) -1){
		printf("Shared Memory Buffer Create Failed...\n");
		return;
	}

	while(1)
	{
		char SendMsg[1023];
		scanf("%s", &SendMsg);
		sprintf((char *)pShmSendBuffer, "%s", SendMsg);

		if(!strcmp(SendMsg,"quit")){
			printf("Quit!\n");
			break;
		}
	}

	if (-1 != shmdt( pShmSendBuffer))
		printf("Shared Memory Release Success!\n");
	else
		printf("Shared Memory Release Failed..\n");

	if ( -1 != shmctl( nShmId, IPC_RMID, 0))
		printf( "Shared Memory Delete Success!\n");
	else
		printf( "Shared Memory Delete Failed..\n");

	return;
}














void test( void)
{
	int   nShmId;
	void *pShmSendBuffer;

	nShmId = shmget((key_t)9999, 1024, IPC_CREAT | 0666);

	if (-1 == nShmId) 
	{
		printf( "Shared Memory Create Failed...\n");
		return;
	}

	pShmSendBuffer = shmat(nShmId, NULL, 0);
	if(pShmSendBuffer == (void *) -1){
		printf( "Shared Memory Buffer Create Failed...\n");
		return;
	}

	while(1)
	{
		printf("%s\n", (char *)pShmSendBuffer);   

		if(!strcmp(pShmSendBuffer,"quit")){
			printf("Quit!\n");
			break;
		}
		sleep(1);
	}

	if (-1 != shmdt( pShmSendBuffer))
		 printf("Shared Memory Release Success!\n");
	else
		 printf("Shared Memory Release Failed..\n");

	return;
}