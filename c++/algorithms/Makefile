CC = g++

WARNINGS = -Wall -Werror	
STANDARD = -std=c++14 -fsanitize=address,undefined 
CFLAGS = $(STANDARD) $(WARNINGS)

all: template dfs

template: template.o
	$(CC) $(CFLAGS) template.o -o template

template.o: template.cpp
	$(CC) $(CFLAGS) template.cpp -c -o template.o

bfs: bfs.o
	$(CC) $(CFLAGS) bfs.o -o bfs

bfs.o: bfs.cpp
	$(CC) $(CFLAGS) bfs.cpp -c -o bfs.o

dfs: dfs.o
	$(CC) $(CFLAGS) dfs.o -o dfs

dfs.o: dfs.cpp
	$(CC) $(CFLAGS) dfs.cpp -c -o dfs.o

binary_search: binary_search.o
	$(CC) $(CFLAGS) binary_search.o -o binary_search

binary_search.o: binary_search.cpp
	$(CC) $(CFLAGS) binary_search.cpp -c -o binary_search.o

run_tempate: template
	make clear
	clear
	./template

run_dfs: dfs
	make clear
	clear
	./dfs

run_bfs: bfs
	make clear
	clear
	./bfs

run_binary_search: binary_search
	make clear
	clear
	./binary_search

clear:
	rm *.o
