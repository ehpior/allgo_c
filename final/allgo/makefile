CC = gcc
TARGET = allgo1

all: $(TARGET)

$(TARGET) : allgo1.o
	$(CC) -o $(TARGET) ../tmp/util.o allgo1.o -I/usr/local/include/mysql -L/usr/local/lib/mysql -lmysqlclient

allgo1.o : allgo1.c
	$(CC) -c -o allgo1.o allgo1.c -I/usr/local/include/mysql -L/usr/local/lib/mysql -lmysqlclient

clean:
	rm allgo1 allgo1.o
