CC=gcc
CFLAGS=-Wextra -Wall -pedantic

all: cim.o test

cim.o: src/cim.c
	$(CC) $(CFLAGS) -c src/cim.c -o cim.o
	mv -f cim.o libs/

test: test/bm_test.c libs/cim.o
	$(CC) $(CFLAGS) test/bm_test.c libs/cim.o -o test/bm_test

clean:
	rm -f test/bm_test libs/*