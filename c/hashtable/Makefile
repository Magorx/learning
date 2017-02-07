CC = clang

WARNINGS = -Wall -Werror	
STANDARD =  
CFLAGS = $(STANDARD) $(WARNINGS)

all: hashtable

hashtable: main.o general.o hashtable.o list.o
	$(CC) $(CFLAGS) main.o general.o hashtable.o list.o -o hashtable

hashtable.o: hashtable.c
	$(CC) $(CFLAGS) hashtable.c -c -o hashtable.o

general.o: general.c
	$(CC) $(CFLAGS) general.c -c -o general.o

main.o: main.c
	$(CC) $(CFLAGS) main.c -c -o main.o

list.o: list.c
	$(CC) $(CFLAGS) list.c -c -o list.o

run: hashtable
	make clear
	clear
	./hashtable

clear:
	rm *.o
