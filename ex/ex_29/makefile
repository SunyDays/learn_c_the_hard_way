CC = gcc
CFLAGS = -Wall -Wextra -g

all: ex_29

ex_29: CFLAGS = -Wall -Wextra -g -DNDEBUG -ldl
ex_29: ex_29_lib.so
	$(CC) ex_29.c -o ../bin/$@ $(CFLAGS)

ex_29_lib.so: CFLAGS = -Wall -Wextra -g -shared -fPIC
ex_29_lib.so: ex_29_lib.o
	$(CC) bin/ex_29_lib.o -o bin/$@ $(CFLAGS)

ex_29_lib.o:
	$(CC) -c ex_29_lib.c -o bin/$@ $(CFLAGS)

clean: remove_temp
	rm -f bin/*

remove_temp:
	rm -f *~
