CC = g++

WARNINGS = -Wall -Werror	
STANDARD = -std=c++11
CFLAGS = $(STANDARD) $(WARNINGS)

all: test

test: test.o
	$(CC) $(CFLAGS) test.o -o test

test.o: test.cpp
	$(CC) $(CFLAGS) test.cpp -c -o test.o

run: test
	make clear
	clear
	./test

clear:
	rm *.o
