CC = clang

all: list

list: main.o general.o list.o
	$(CC) main.o general.o list.o -o list

list.o: list.c
	$(CC) list.c -c -o list.o

general.o: general.c
	$(CC) general.c -c -o general.o

main.o: main.c
	$(CC) main.c -c -o main.o

clear:
	rm *.o