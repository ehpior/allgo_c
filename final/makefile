CC = gcc
TARGET1 = cheg
TARGET2 = program

all : util.o cheg.o program.o
	$(CC) -o cheg tmp/util.o tmp/cheg.o -I /usr/local/include/hiredis/ -lhiredis
	$(CC) -o program tmp/util.o tmp/program.o -I /usr/local/include/hiredis/ -lhiredis

util.o : util/util.c
	$(CC) -c -o tmp/util.o util/util.c

cheg.o : cheg.c
	$(CC) -c -o tmp/cheg.o cheg.c -I/usr/local/include/mysql -L/usr/local/lib/mysql -lmysqlclient -I /usr/local/include/hiredis/ -lhiredis

program.o : program.c
	$(CC) -c -o tmp/program.o program.c -I/usr/local/include/mysql -L/usr/local/lib/mysql -lmysqlclient -I /usr/local/include/hiredis/ -lhiredis

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
