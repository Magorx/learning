CC = clang

WARNINGS = -Wall -Werror	
STANDARD =  
CFLAGS = $(STANDARD) $(WARNINGS)

all: list

list: main.o general.o list.o
	$(CC) $(CFLAGS) main.o general.o list.o -o list

list.o: list.c
	$(CC) $(CFLAGS) list.c -c -o list.o

general.o: general.c
	$(CC) $(CFLAGS) general.c -c -o general.o

main.o: main.c
	$(CC) $(CFLAGS) main.c -c -o main.o

clear:
	rm *.o
