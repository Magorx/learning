CC = g++

WARNINGS = -Wall -Werror	
STANDARD = -std=c++14 -fsanitize=address,undefined 
CFLAGS = $(STANDARD) $(WARNINGS)

all: template test

template: template.o
	$(CC) $(CFLAGS) template.o -o template

template.o: template.cpp
	$(CC) $(CFLAGS) template.cpp -c -o template.o

test: test.o
	$(CC) $(CFLAGS) test.o -o test

test.o: test.cpp
	$(CC) $(CFLAGS) test.cpp -c -o test.o

run: template
	make clear
	clear
	./template

run_test: test
	make clear
	clear
	./test

clear:
	rm *.o
