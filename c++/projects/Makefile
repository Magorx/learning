CC = g++

WARNINGS = -Wall -Werror	
STANDARD = -std=c++14 -fsanitize=address,undefined 
CFLAGS = $(STANDARD) $(WARNINGS)

all: calculator

calculator: calculator.o main.o
	$(CC) $(CFLAGS) calculator.o main.o -o calculator

calculator.o: calculator.cpp
	$(CC) $(CFLAGS) calculator.cpp -c -o calculator.o

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp -c -o main.o

run: calculator
	make clear
	clear
	./calculator

clear:
	rm *.o

