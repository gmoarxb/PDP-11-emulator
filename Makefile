CC=gcc
CFLAGS=-Wall -Wextra -std=c11
LFLAGS=`pkg-config --cflags --libs check`

OBJFILES=./objfiles/*

all: compile_memory compile_support
	$(CC) $(CFLAGS) -c ./main.c
	$(CC) $(CFLAGS) main.o $(OBJFILES) -o ./pdp11.out

run: all
	./pdp11.out

test: compile_memory compile_support
	$(CC) $(CFLAGS) -c ./test/test_main.c $(LFLAGS)
	$(CC) $(CFLAGS) test_main.o $(OBJFILES) -o ./pdp11_test.out $(LFLAGS)

test_run: test
	./pdp11_test.out

compile_memory:
	$(CC) $(CFLAGS) -c ./memory/write_read.c -o ./objfiles/write_read.o
	$(CC) $(CFLAGS) -c ./memory/load_dump.c -o ./objfiles/load_dump.o

compile_support:
	$(CC) $(CFLAGS) -c ./support/error.c -o ./objfiles/error.o
	$(CC) $(CFLAGS) -c ./support/word.c -o ./objfiles/word.o
	
clean:
	rm *.o *.out ./objfiles/*