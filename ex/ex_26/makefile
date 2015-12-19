CC = gcc
PREFIX ?= /usr/local
CFLAGS = -Wall -Wextra -g -I ${PREFIX}/apr/include/apr-1 -I ${PREFIX}/apr/include/apr-util-1
LDFLAGS = -L ${PREFIX}/apr/lib -lapr-1 -pthread -laprutil-1

all:devpkg

devpkg: bstrlib.o db.o shell.o commands.o

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
