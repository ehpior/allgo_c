#include "com_allgo_web_jni_RealJNI.h"
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>    //write
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <wchar.h>
#include <sys/shm.h>

//#include "real_cheg.h"
//#include "real_program.h"

#pragma pack(1)
typedef struct kospi{
    int cnt;
    char code[6];
}kospi;

typedef struct kosdaq{
    int cnt;
    char code[6];
}kosdaq;
#pragma pack()

/* 0 = read/write, 1 = read
9 kospi_cnt, 99 kosdaq_cnt, 999 real_program, 9999 real_cheg */
char *shm_get(key_t key, int size, int mode){

    char *shm_data = NULL;

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

JNIEXPORT void JNICALL Java_com_allgo_web_jni_RealJNI_updateCnt(JNIEnv *env, jobject obj)
{
    /*char *kospi_cnt_shm = shm_get(9, 10, 0);
    char *kosdaq_cnt_shm = shm_get(99, 10, 0);

    sprintf(kospi_cnt_shm, "%d", 1500);
    sprintf(kosdaq_cnt_shm, "%d", 2500);*/


    kospi *kospi_data = (kospi *)shm_get(9, sizeof(kospi), 0);
    //kosdaq *kosdaq_data = (kosdaq *)shm_get(999, sizeof(kosdaq), 0);
    if(kospi_data == NULL){
        return ;
    }

    int kospi_cnt = kospi_data->cnt + 1;
    //int kosdaq_cnt = kosdaq_data->cnt + 1;

    kospi_data->cnt = kospi_cnt;
    //kosdaq_data->cnt = kosdaq_cnt;

	jclass cls = (*env)->GetObjectClass(env, obj);

	jfieldID fid = (*env)->GetFieldID(env, cls, "kospi_cnt", "I");
	(*env)->SetIntField(env, obj, fid, kospi_cnt);

    /*jfieldID fid2 = (*env)->GetFieldID(env, cls, "kosdaq_cnt", "I");
    (*env)->SetIntField(env, obj, fid2, kosdaq_cnt);*/
}

JNIEXPORT void JNICALL Java_com_allgo_web_jni_RealJNI_updateRealCheg(JNIEnv *env, jobject obj, jobjectArray array)
{
    kospi *kospi_data = (kospi *)shm_get(9, sizeof(struct kospi), 0);

    kospi_data->cnt = 1500;

}

JNIEXPORT void JNICALL Java_com_allgo_web_jni_RealJNI_updateRealProgram(JNIEnv *env, jobject obj, jobjectArray array)
{
    kosdaq *kosdaq_data = (kosdaq *)shm_get(999, sizeof(struct kosdaq), 0);

    kosdaq_data->cnt = 2500;
}
