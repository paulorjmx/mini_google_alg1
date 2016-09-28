all: main.o list.o interface.o keywords.o
	@gcc obj/list.o obj/main.o obj/keywords.o obj/interface.o -o main

main.o: main.c
	@gcc -c main.c -o obj/main.o

list.o: list.c
	@gcc -c list.c -o obj/list.o

interface.o: interface.c
	@gcc -c interface.c -o obj/interface.o

keywords.o: keywords.c
	@gcc -c keywords.c -o obj/keywords.o

clean:
	rm obj/*.o
