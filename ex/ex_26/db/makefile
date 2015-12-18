CC = gcc
PREFIX? = /usr/local
CFLAGS = -Wall -Wextra -g -I /usr/local/apr/include/apr-1 -I /usr/local/apr/include/apr-util-1
LDFLAGS = -L ${PREFIX}/apr/lib -lapr-1 -pthread -laprutil-1

all: db.o

db.o:
	$(CC) -c db.c -o ../bin/$@ $(CFLAGS)

clean: remove_temp
	rm -f ../bin/db.o

remove_temp:
	rm -f *~
