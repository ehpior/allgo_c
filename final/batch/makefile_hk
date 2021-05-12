CC = gcc
TARGET = daily_cheg
TARGET2 = daily_program

all : $(TARGET) $(TARGET2)

$(TARGET): daily_cheg.o
	$(CC) -o daily_cheg tmp/daily_cheg.o ../tmp/util.o -I/usr/local/include/mysql -L/usr/local/lib/mysql -lmysqlclient

$(TARGET2): daily_program.o
	$(CC) -o daily_program tmp/daily_program.o ../tmp/util.o -I/usr/local/include/mysql -L/usr/local/lib/mysql -lmysqlclient

daily_cheg.o: daily_cheg.c
	$(CC) -c -o tmp/daily_cheg.o daily_cheg.c -I/usr/local/include/mysql -L/usr/local/lib/mysql -lmysqlclient

daily_program.o: daily_program.c
	$(CC) -c -o tmp/daily_program.o daily_program.c -I/usr/local/include/mysql -L/usr/local/lib/mysql -lmysqlclient

clean :
	rm $(TARGET) tmp/$(TARGET).o $(TARGET2) tmp/$(TARGET2).o
