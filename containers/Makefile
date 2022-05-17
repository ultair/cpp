CC=g++

CFLAGS=-std=c++17 -Wpedantic -g

all: hashmap testdeque

.PHONY: all

hashmap: hashmap.cpp
	$(CC) $(CFLAGS) -o $@ $^

testdeque: testdeque.cpp
	$(CC) $(CFLAGS) -lUnitTest++ -o $@ $^

.PHONY: clean

clean:
	rm -f hashmap testdeque
