CC= gcc
CFLAGS= -Wall -g #-std=c11
LIB=lib/
LDFLAGS= -lcrypt 
INC=include/
EXEC= src/main.exe
SRC= src/main.c
OBJ= $(SRC:.c=.o)

all : $(EXEC)

$(EXEC) : main.c
	$(CC) $< -o $@ $(CFLAGS) $(LDFLAGS) -I $(INC) -L $(LIB)

clean:
	rm *.exe *.o
