CC = gcc
TARGET = a.out

$(TARGET) : util.o udp_recv_test.o
	$(CC) -o $(TARGET) tmp/util.o tmp/udp_recv_test.o

util.o : util/util.c
	$(CC) -c -o tmp/util.o util/util.c

udp_recv_test.o : udp_recv_test.c
	$(CC) -c -o tmp/udp_recv_test.o udp_recv_test.c -I/usr/local/include/mysql -L/usr/local/lib/mysql -lmysqlclient

clean :
	rm -f tmp/*