CC = gcc
PREFIX ?= /usr/local
CFLAGS = -Wall -Wextra -g -I ${PREFIX}/apr/include/apr-1 -I ${PREFIX}/apr/include/apr-util-1
LDFLAGS = -L ${PREFIX}/apr/lib -lapr-1 -pthread -laprutil-1

all: devpkg

devpkg: devpkg.o bstrlib.o db.o shell.o commands.o
	$(CC) bin/devpkg.o bin/bstrlib.o bin/db.o bin/shell.o bin/commands.o -o ../bin/$@ $(CFLAGS) $(LDFLAGS)

devpkg.o:
	$(CC) -c devpkg.c -o bin/$@ $(CFLAGS)

bstrlib.o:
	make -C bstrlib/

db.o:
	make -C db/

shell.o:
	make -C shell/

commands.o:
	make -C commands/

install: all
	install -d $(DESTDIR)/$(PREFIX)/bin/
	install devpkg $(DESTDIR)/$(PREFIX)/bin/

clean: remove_temp
	rm -f bin/*
	rm -f devpkg
	rm -rf *.dSYM

remove_temp:
	rm -f *~
	make remove_temp -C bstrlib/
	make remove_temp -C db/
	make remove_temp -C shell/	
	make remove_temp -C commands/
