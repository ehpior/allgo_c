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

#include "real_cheg.h"
#include "real_program.h"

#define REAL_CHEG_SHM 999
#define REAL_PROGRAM_SHM 9999

#define SHM_READWRITE 0
#define SHM_READ 1

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

real_cheg_data *cur_cheg_data;

JNIEXPORT void JNICALL Java_com_allgo_web_jni_RealJNI_updateRealCheg(JNIEnv *env, jobject obj, jobjectArray stockArr)
{
    cur_cheg_data = (real_cheg_data*) shm_get(REAL_CHEG_SHM, sizeof(real_cheg_data), SHM_READ);

    if(cur_cheg_data == NULL){
        return;
    }

    char code[6+1];
    int price = 0;

    jobject stockUnit;
	jclass stockCls;
	jfieldID fid;
    jstring jStr;

    int i = 0;
	for( i = 0; i < 3000; i++ ) {
        real_cheg cur_cheg = cur_cheg_data->data[i];

        memset(code, 0x00, sizeof(code));
        memcpy(code, cur_cheg.code, 6);
        price = cur_cheg.price;

        stockUnit = (*env)->GetObjectArrayElement(env, stockArr, i);
        stockCls = (*env)->GetObjectClass(env, stockUnit);

        /* code */
        fid = (*env)->GetFieldID(env, stockCls, "code", "Ljava/lang/String;");
        if( fid == 0 ) {
            return;
        }
        jStr = (*env)->NewStringUTF(env, code);
        if( jStr == NULL ) {
            return;
        }
        (*env)->SetObjectField(env, stockUnit, fid, jStr);
        (*env)->DeleteLocalRef(env, jStr);

        /* price */
        fid = (*env)->GetFieldID(env, stockCls, "price", "I");
        if( fid == 0 ) {
            return;
        }
        (*env)->SetIntField(env, stockUnit, fid, price);
    }
}

real_program_data *cur_program_data;

JNIEXPORT void JNICALL Java_com_allgo_web_jni_RealJNI_updateRealProgram(JNIEnv *env, jobject obj, jobjectArray stockArr)
{
    cur_program_data = (real_program_data*) shm_get(REAL_PROGRAM_SHM, sizeof(real_program_data), SHM_READ);

    if(cur_program_data == NULL){
        return;
    }

    char code[6+1];
    int price = 0;

    jobject stockUnit;
	jclass stockCls;
	jfieldID fid;
    jstring jStr;

    int i = 0;
	for( i = 0; i < 3000; i++ ) {
        real_program cur_program = cur_program_data->data[i];

        memset(code, 0x00, sizeof(code));
        memcpy(code, cur_program.code, 6);
        price = cur_program.price;

        stockUnit = (*env)->GetObjectArrayElement(env, stockArr, i);
        stockCls = (*env)->GetObjectClass(env, stockUnit);

        /* code */
        fid = (*env)->GetFieldID(env, stockCls, "code", "Ljava/lang/String;");
        if( fid == 0 ) {
            return;
        }
        jStr = (*env)->NewStringUTF(env, code);
        if( jStr == NULL ) {
            return;
        }
        (*env)->SetObjectField(env, stockUnit, fid, jStr);
        (*env)->DeleteLocalRef(env, jStr);

        /* price */
        fid = (*env)->GetFieldID(env, stockCls, "price", "I");
        if( fid == 0 ) {
            return;
        }
        (*env)->SetIntField(env, stockUnit, fid, price);
    }
}
