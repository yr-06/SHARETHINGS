CC= gcc
CFLAGS= -Wall -g #-std=c11
LIB= ../lib
LIDFLAGS= -lcrypt
INC= ../include
EXEC= main.exe
SRC= main.c
OBJ= $(SRC:.c=.o)

all : $(EXEC)

$(EXEC) : main.c
	$(CC) $< -o $@ $(CFLAGS) $(LDFLAGS) -I $(INC) -L $(LIB)

clean:
	rm *.exe *.o
