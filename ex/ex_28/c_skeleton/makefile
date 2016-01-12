CC = gcc
CFLAGS = -g -02 -Wall -Wextra -Isrc -rdynamic -NDEBUG $(OPTFLAGS)
LIBS = -ldl $(OPTLIBS)
PREFIX ?= /usr/local

SOURCES = $(wildcard src/**/*.c src/*.c)
OBJECTS = $(patsubst %.c,%.o,$(SOURCES))

TEST_SRC = $(wildcard tests/*_tests.c)
TESTS = $(patsubst %.c,%,$(TEST_SRC))

TARGET = build/libYOUR_LIBRARY.a
SO_TARGET = $(patsubst %.a,%.so,$(TARGET))

# target biuld
all: $(TARGET) $(SO_TARGET) tests

dev: CFLAGS = -g -Wall -Wextra -Isrc $(OPTFLAGS)
dev: all

$(TARGET): CFLAGS += -fPIC
$(TARGET): build $(OBJECTS)
	ar rcs $@ $(OBJECTS)
	ranlib $@

$(SO_TARGET): $(TARGET) $(OBJECTS)
	$(CC) -shared -o $@ $(OBJECTS)

build:
	@mkdir -p build
	@mkdir -p bin

# unit tests
.PHONY: tests

tests: CFLAGS += $(TARGET)
tests: $(TESTS)
	sh ./tests/runtests.sh

valgrind:
	VALGRING = "valgrind --log-file=/tmp/valgrind-%p.log" $(MAKE)

# cleaner
clean:
	rm -rf build $(OBJECTS) $(TESTS)
	rm -f tests/tests.log
	find . -name  "*.gc" -exec rm {} \;
	rm -rf 'find . -name "*.dSYM" -print'

# install
install: all
	install -d $(DESTDIR)/$(PREFIX)/lib/
	install $(TARGET) $(DESTDIR)/$(PREFIX)/lib/

# checker
BADFUNCS = '[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)|stpn?cpy|a?sn?prinrf|byte_)'

check:
	@echo Files with potentially dangerous functions.
	@egrep $(BADFUNCS) $(SOURCES) || true
