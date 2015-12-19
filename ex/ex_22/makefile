CC = gcc
CFLAGS = -Wall -Wextra -g

all: ex_22_main

ex_22_main: ex_22.o ex_22_main.o
	$(CC) bin/ex_22.o bin/ex_22_main.o -o ../bin/$@ $(CFLAGS)

ex_22_main.o:
	$(CC) -c ex_22_main.c -o bin/$@ $(CFLAGS)

ex_22.o:
	$(CC) -c ex_22.c -o bin/$@ $(CFLAGS)

clean: remove_temp
	rm -f bin/*

remove_temp:
	rm -f *~
