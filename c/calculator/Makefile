CC = clang

WARNINGS = -Wall -Werror	
STANDARD =  
CFLAGS = $(STANDARD) $(WARNINGS)

all: calculator test_calculator

calculator: main.o calculator.o general.o
	$(CC) $(CFLAGS) main.o calculator.o -lm general.o -o calculator

test_calculator: main_test.o
	$(CC) $(CFLAGS) main_test.o calculator.o -lm general.o -o test_calculator

calculator.o: calculator.c
	$(CC) $(CFLAGS) calculator.c -c -o calculator.o

main.o: main.c
	$(CC) $(CFLAGS) main.c -c -o main.o

main_test.o: main_test.c
	$(CC) $(CFLAGS) main_test.c -c -o main_test.o

general.o: general.c
	$(CC) $(CFALGS) general.c -c -o general.o

run: calculator
	make clear
	clear
	./calculator

clear:
	rm *.o
