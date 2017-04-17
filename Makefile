CFLAGS=-c -Wall

all: main

main: main.o hexdump.o
	gcc main.o hexdump.o -o main

hexdump.o: hexdump.c
	gcc $(CFLAGS) hexdump.c

main.o: main.c
	gcc $(CFLAGS) main.c

clean :
	rm *.o main
