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
    char *kospi_cnt_shm = shm_get(9, 10, 0);
    char *kosdaq_cnt_shm = shm_get(99, 10, 0);

    sprintf(kospi_cnt_shm, "%d", 1500);
    sprintf(kosdaq_cnt_shm, "%d", 2500);

    /*int kospi_cnt = atoi(shm_get(9, 4, 0));
    int kosdaq_cnt = atoi(shm_get(99, 4, 0));*/

	jclass cls = (*env)->GetObjectClass(env, obj);
	jfieldID fid = (*env)->GetFieldID(env, cls, "kospi_cnt", "I");
    jfieldID fid2 = (*env)->GetFieldID(env, cls, "kosdaq_cnt", "I");

	(*env)->SetIntField(env, obj, fid, atoi(kospi_cnt_shm));
    (*env)->SetIntField(env, obj, fid2, atoi(kosdaq_cnt_shm));
}

JNIEXPORT void JNICALL Java_com_allgo_web_jni_RealJNI_updateRealCheg(JNIEnv *env, jobject obj, jobjectArray array)
{

}

JNIEXPORT void JNICALL Java_com_allgo_web_jni_RealJNI_updateRealProgram(JNIEnv *env, jobject obj, jobjectArray array)
{

}
