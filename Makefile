MAKE = make

GCC = gcc

LIBFLAGS = -lcrypt

CFLAGS =-Wall -g #-std=c11 -lcrypt

INCLUDE = include/

SRC = $(wildcard src/*.c)

MOVE = mv

EXC = ./src/main.exe

LIB = lib/

BIN = bin/*

LOG = log/*


all :
	@mkdir -p lib

	$(MAKE) compile -s

	$(MAKE) run -s

compile :

	@$(GCC) $(CFLAGS) -I $(INCLUDE) -c $(SRC) $(LIBFLAGS)

	@$(MOVE) *.o $(LIB)

	@$(GCC) $(CFLAGS) -o $(EXC) $(LIB)*.o $(LIBFLAGS)


run :

	@$(EXC)


clean :

	rm $(EXC)

	rm $(LIB)*
