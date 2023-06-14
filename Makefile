CC=gcc
CFLAGS=-Wall -Wextra -std=c11
LFLAGS=`pkg-config --cflags --libs check`

all: memwr err
	$(CC) $(CFLAGS) -c ./main.c
	$(CC) $(CFLAGS) main.o memory_wr.o error.o -o ./pdp11.out

run: all
	./pdp11.out

memwr:
	$(CC) $(CFLAGS) -c ./memory_wr.c

err:
	$(CC) $(CFLAGS) -c ./error.c

test: memwr err
	$(CC) $(CFLAGS) -c ./test/test_main.c $(LFLAGS)
	$(CC) $(CFLAGS) test_main.o memory_wr.o error.o -o ./pdp11_test.out $(LFLAGS)

test_run: test
	./pdp11_test.out
clean:
	rm *.o *.out