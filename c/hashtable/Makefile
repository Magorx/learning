CC = clang

WARNINGS = -Wall -Werror	
STANDARD =  
CFLAGS = $(STANDARD) $(WARNINGS)

all: hashtable

list: main.o general.o hashtable.o
	$(CC) $(CFLAGS) main.o general.o list.o -o list

hashtable.o: hashtable.c
	$(CC) $(CFLAGS) hashtable.c -c -o hashtable.o

general.o: general.c
	$(CC) $(CFLAGS) general.c -c -o general.o

main.o: main.c
	$(CC) $(CFLAGS) main.c -c -o main.o

clear:
	rm *.o
