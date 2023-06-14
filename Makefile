CC=gcc
CFLAGS=-Wall -Wextra -Werror -Wpedantic -pedantic-errors -std=c11
LFLAGS=-lgcov -lcheck

all:
	$(CC) $(CFLAGS) ./main.c

test:
	$(CC) $(CFLAGS) ./test/test_main.c

clean:
	rm *.out