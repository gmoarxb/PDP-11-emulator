CC=gcc
CFLAGS=-Wall -Wextra -std=c11
LFLAGS=`pkg-config --cflags --libs check`

OBJFILES=memory_wr.o error.o word.o memory_ld.o

all: memwr err wordf memld
	$(CC) $(CFLAGS) -c ./main.c
	$(CC) $(CFLAGS) main.o $(OBJFILES) -o ./pdp11.out

run: all
	./pdp11.out

memwr:
	$(CC) $(CFLAGS) -c ./memory_wr.c

memld:
	$(CC) $(CFLAGS) -c ./memory_ld.c

err:
	$(CC) $(CFLAGS) -c ./error.c

wordf:
	$(CC) $(CFLAGS) -c ./word.c

test: memwr err wordf memld
	$(CC) $(CFLAGS) -c ./test/test_main.c $(LFLAGS)
	$(CC) $(CFLAGS) test_main.o $(OBJFILES) -o ./pdp11_test.out $(LFLAGS)

test_run: test
	./pdp11_test.out
	
clean:
	rm *.o *.out