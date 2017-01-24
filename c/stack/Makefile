CC = clang

all: stack.out	

stack.out: main.o general.o stack.o
	$(CC) main.o general.o stack.o -o stack.out

stack.o: stack.c
	$(CC) stack.c -c -o stack.o

general.o: general.c
	$(CC) general.c -c -o general.o

main.o: main.c
	$(CC) main.c -c -o main.o

clear:
	rm *.o stack.out