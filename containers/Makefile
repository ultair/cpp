CC=g++

CFLAGS=-std=c++17 -Wpedantic -g

all: testhashmap testdeque

.PHONY: all

testhashmap: testhashmap.cpp
	$(CC) $(CFLAGS) -lUnitTest++ -o $@ $^

testdeque: testdeque.cpp
	$(CC) $(CFLAGS) -lUnitTest++ -o $@ $^

.PHONY: clean

clean:
	rm -f testhashmap testdeque
