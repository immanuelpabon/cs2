CC = gcc
CFLAGS= -g -Wall -ansi -O0
OBJECTS = main.o

main: $(OBJECTS)
	$(CC) $(CFLAGS) -o main $(OBJECTS)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

clean:
	rm main $(OBJECTS)

test: main
	valgrind --leak-check=full ./main
