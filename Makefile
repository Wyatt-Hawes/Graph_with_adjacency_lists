CC = gcc
CFLAGS = -std=c17 -Wall -Werror -Wextra -Wpedantic -g#$(shell pkg-config --cflags)

all: GraphTest FindPath

FindPath: FindPath.o Graph.o List.o
	$(CC) -o $@ $^
GraphTest: GraphTest.o Graph.o List.o
	$(CC) -o $@ $^


%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean: spotless
	rm -f *.o
	
spotless: clean
	rm -f GraphTest FindPath
