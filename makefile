CC=gcc
CFLAGS=-Wextra -Wall -pedantic

all: filters opencim test

opencim: src/cim.c libs/filters.o
	$(CC) $(CFLAGS) -c src/cim.c libs/filters.o -o cim.o
	mv -f cim.o libs/

filters: src/filters.c
	$(CC) $(CFLAGS) -c src/filters.c -o filters.o
	mv -f filters.o libs/

test: test/bm_test.c test/png_test.c libs/cim.o libs/filters.o
	$(CC) $(CFLAGS) test/bm_test.c libs/cim.o libs/filters.o -o test/bm_test
	$(CC) $(CFLAGS) test/png_test.c libs/cim.o libs/filters.o -o test/png_test

clean:
	rm -f test/*_test libs/*