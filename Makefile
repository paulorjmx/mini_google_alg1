all: main.o list.o interface.o
	@gcc list.o main.o interface.o -o main

main.o: main.c
	@gcc -c main.c -o main.o

list.o: list.c
	@gcc -c list.c -o list.o

interface.o: interface.c
	@gcc -c interface.c -o interface.o

clean:
	@rm *.o
