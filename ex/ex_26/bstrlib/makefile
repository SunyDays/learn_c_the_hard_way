CC = gcc
PREFIX ?= /usr/local
CFLAGS = -Wall -Wextra -g -I ${PREFIX}/apr/include/apr-1 -I ${PREFIX}/apr/include/apr-util-1
LDFLAGS = -L ${PREFIX}/apr/lib -lapr-1 -pthread -laprutil-1

all: bstrlib.o

bstrlib.o:
	$(CC) -c bstrlib.c -o ../bin/$@ $(CFLAGS)

clean: remove_temp
	rm -f ../bin/bstrlib.o

remove_temp:
	rm -f *~
