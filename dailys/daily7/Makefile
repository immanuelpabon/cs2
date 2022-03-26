CC=gcc
CFLAGS=-g -O0 -Wall -ansi

all: main

main: main.o
	$(CC) $(CFLAGS) -o main main.o
main.o: main.c
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o main
