CC = gcc
TARGET1 = recv_real_cheg
TARGET2 = recv_real_program

all : util.o recv_real_cheg.o recv_real_program.o
	$(CC) -o cheg tmp/util.o tmp/recv_real_cheg.o
	$(CC) -o program tmp/util.o tmp/recv_real_program.o

util.o : util/util.c
	$(CC) -c -o tmp/util.o util/util.c

recv_real_cheg.o : recv_real_cheg.c
	$(CC) -c -o tmp/recv_real_cheg.o recv_real_cheg.c -I/usr/local/include/mysql -L/usr/local/lib/mysql -lmysqlclient

recv_real_program.o : recv_real_program.c
	$(CC) -c -o tmp/recv_real_program.o recv_real_program.c -I/usr/local/include/mysql -L/usr/local/lib/mysql -lmysqlclient

clean :
	rm -f tmp/*

#mysql.h 없을 시 다운
#apt-get install libmysqlclient-dev

#mysql.h 위치 찾는 명령어
#mysql_config --cflags 

#include  mysql.h 방법
#include "/usr/include/mysql/mysql.h"     (위에서 찾은 위치경로를 입력합니다)

#컴파일 방법
#gcc -o sqlprogtam sqlprogram.c -lmysqlclient
