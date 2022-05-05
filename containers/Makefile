CC=g++

CFLAGS=-std=c++17 -Wpedantic

all: hashmap deque

.PHONY: all

hashmap: hashmap.cpp
	$(CC) $(CFLAGS) -o $@ $^

deque: deque.cpp
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean

clean:
	rm -f hashmap deque
