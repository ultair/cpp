CC=g++

CFLAGS=-std=c++17 -Wpedantic -g

all: hashmap testdeque rundeque

.PHONY: all

hashmap: hashmap.cpp
	$(CC) $(CFLAGS) -o $@ $^

testdeque: testdeque.cpp
	$(CC) $(CFLAGS) -lUnitTest++ -o $@ $^

rundeque: rundeque.cpp
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean

clean:
	rm -f hashmap testdeque rundeque
