CC = g++

WARNINGS = -Wall -Werror	
STANDARD = -std=c++11
CFLAGS = $(STANDARD) $(WARNINGS)

all: easy_task

easy_task: easy_task.o
	$(CC) $(CFLAGS) easy_task.o -o easy_task

easy_task.o: easy_task.cpp
	$(CC) $(CFLAGS) easy_task.cpp -c -o easy_task.o

run: easy_task
	make clear
	clear
	./easy_task

clear:
	rm *.o
