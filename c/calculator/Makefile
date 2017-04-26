CC = clang

WARNINGS = -Wall -Werror	
STANDARD =  
CFLAGS = $(STANDARD) $(WARNINGS)

all: calculator

calculator: main.o calculator.o general.o
	$(CC) $(CFLAGS) main.o calculator.o -lm general.o -o calculator

calculator.o: calculator.c
	$(CC) $(CFLAGS) calculator.c -c -o calculator.o

main.o: main.c
	$(CC) $(CFLAGS) main.c -c -o main.o

general.o: general.c
	$(CC) $(CFALGS) general.c -c -o general.o

run: calculator
	make clear
	clear
	./calculator

clear:
	rm *.o
