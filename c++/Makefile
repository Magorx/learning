CC = g++

WARNINGS = -Wall -Werror	
STANDARD = -std=c++11
CFLAGS = $(STANDARD) $(WARNINGS)

all: template

template: template.o
	$(CC) $(CFLAGS) template.o -o template

template.o: template.cpp
	$(CC) $(CFLAGS) template.cpp -c -o template.o

run: template
	make clear
	clear
	./template

clear:
	rm *.o
