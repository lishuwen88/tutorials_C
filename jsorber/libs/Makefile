

CC=clang
CFLAGS=-Wall -g
BINS=librarytest libmycode.so runtime_librarytest libmystaticcode.a static_librarytest

all: $(BINS)

libmycode.o: libmycode.c mycode.h
	$(CC) $(CFLAGS) -c libmycode.c

libmycode.so: libmycode.c mycode.h
	$(CC) $(CFLAGS) -fPIC -shared -o $@ libmycode.c -lc

libmystaticcode.a: libmycode.o
	ar rcs libmystaticcode.a libmycode.o

librarytest: librarytest.c libmycode.o
	$(CC) $(CFLAGS) -o $@ $^

runtime_librarytest: librarytest.c
	$(CC) $(CFLAGS) -o $@ $^ -L. -lmycode

static_librarytest: librarytest.c
	$(CC) $(CFLAGS) -o $@ $^ -L. -lmystaticcode
clean:
	rm *.o $(BINS)
