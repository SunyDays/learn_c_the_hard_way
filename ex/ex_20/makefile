CC = gcc
CFLAGS = -Wall -Wextra -g

all: ex_20

ex_20:
	$(CC) $@.c -o ../bin/$@ $(CFLAGS)

clean: remove_temp
	rm -f ../bin/ex_20

remove_temp:
	rm -f *~
