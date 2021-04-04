CC = gcc
TARGET = chk_db
TARGET2 = chk_shm
TARGET3 = clear_shm

all : $(TARGET) $(TARGET2) $(TARGET3)

$(TARGET): chk_db.c 
	$(CC) -o chk_db chk_db.c -I/usr/local/include/mysql -L/usr/local/lib/mysql -lmysqlclient

$(TARGET2): chk_shm.c 
	$(CC) -o chk_shm chk_shm.c

$(TARGET3): clear_shm.c 
	$(CC) -o clear_shm clear_shm.c

clean :
	rm $(TARGET) $(TARGET2) $(TARGET3)
