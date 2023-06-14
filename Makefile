CC=gcc
CFLAGS=-Wall -Wextra -std=c11
LFLAGS=`pkg-config --cflags --libs check`

OBJFILES=memory_wr.o error.o endian.o

all: memwr err endi
	$(CC) $(CFLAGS) -c ./main.c
	$(CC) $(CFLAGS) main.o $(OBJFILES) -o ./pdp11.out

run: all
	./pdp11.out

memwr:
	$(CC) $(CFLAGS) -c ./memory_wr.c

err:
	$(CC) $(CFLAGS) -c ./error.c

endi:
	$(CC) $(CFLAGS) -c ./endian.c

test: memwr err endi
	$(CC) $(CFLAGS) -c ./test/test_main.c $(LFLAGS)
	$(CC) $(CFLAGS) test_main.o $(OBJFILES) -o ./pdp11_test.out $(LFLAGS)

test_run: test
	./pdp11_test.out
clean:
	rm *.o *.out