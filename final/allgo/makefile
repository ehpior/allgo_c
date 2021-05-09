CC = gcc
TARGET = allgo1
TARGET2 = allgo2

all: $(TARGET) $(TARGET2)

$(TARGET) : allgo1.o
	$(CC) -o $(TARGET) ../tmp/util.o allgo1.o -I/usr/local/include/mysql -L/usr/local/lib/mysql -lmysqlclient

allgo1.o : allgo1.c
	$(CC) -c -o allgo1.o allgo1.c -I/usr/local/include/mysql -L/usr/local/lib/mysql -lmysqlclient

$(TARGET2) : allgo2.o
	$(CC) -o $(TARGET2) ../tmp/util.o allgo2.o -I/usr/local/include/mysql -L/usr/local/lib/mysql -lmysqlclient

allgo2.o : allgo2.c
	$(CC) -c -o allgo2.o allgo2.c -I/usr/local/include/mysql -L/usr/local/lib/mysql -lmysqlclient

clean:
	rm allgo1 allgo1.o allgo2 allgo2.o
