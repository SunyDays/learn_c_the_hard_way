CC = gcc
CFLAGS = -Wall -Wextra -g

all: ex_19

ex_19: ex_19.o object.o
	$(CC) bin/ex_19.o bin/object.o -o ../bin/$@ $(CFLAGS)

ex_19.o:
	$(CC) -c ex_19.c -o bin/$@ $(CFLAGS)

object.o:
	$(CC) -c object.c -o bin/$@ $(CFLAGS)

clean: remove_temp
	rm -f bin/*

remove_temp:
	rm -f *~
