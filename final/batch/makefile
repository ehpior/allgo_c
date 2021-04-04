CC = gcc
TARGET = daily_cheg

all : $(TARGET)

$(TARGET): daily_cheg.o
	$(CC) -o daily_cheg daily_cheg.o ../tmp/util.o -I/usr/local/include/mysql -L/usr/local/lib/mysql -lmysqlclient

daily_cheg.o: daily_cheg.c
	$(CC) -c -o daily_cheg.o daily_cheg.c -I/usr/local/include/mysql -L/usr/local/lib/mysql -lmysqlclient

clean :
	rm $(TARGET) $(TARGET).o
