CC = gcc
CFLAGS= -g -Wall --std=c99
OBJECTS = main.o bit_flags.o

main: $(OBJECTS)
	$(CC) $(CFLAGS) -o main $(OBJECTS)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

bit_flags.o: bit_flags.h bit_flags.c
	$(CC) $(CFLAGS) -c bit_flags.c -o bit_flags.o

clean:
	rm main $(OBJECTS)

test: main
	./main
