all: main

main: main.o
	gcc main.c -o main

clean :
	rm *.o main
