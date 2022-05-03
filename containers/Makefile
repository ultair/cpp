CC=g++

CFLAGS=-std=c++17 -Wpedantic

all: hashmap

.PHONY: all

hashmap: hashmap.cpp
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean

clean:
	rm -f hashmap
