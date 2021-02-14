SRCINC	= /home/service/fep/src/sise/inc
LIBINC	= /home/service/fep/src/lib/inc
LIB		= /home/service/fep/lib
BIN		= /home/service/fep/bin
LIBS    = -lutil -lmysqlclient
OBJS	= A0.o A3.o A4.o A6.o B1.o C8.o D0.o D2.o D4.o D6.o D8.o E4.o E6.o F1.o F0.o
CFLAGS	= -g -m64 -I/usr/local/include/mariadb -I$(SRCINC) -I$(LIBINC) -L$(LIB) $(OBJS) $(LIBS) 
TARGET	= sise_proc sise_recv

all:	$(TARGET)

$(TARGET):
	$(CC) -o $@ $@.c  $(CFLAGS) 

install: all 
	mv $(TARGET) $(BIN)

clean:
	rm -f $(TARGET) $(OBJS)
