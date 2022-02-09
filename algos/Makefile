CC=g++

CFLAGS=-std=c++17 -Wpedantic

all: quicksort

.PHONY: all

quicksort: quicksort.cpp
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean

clean:
	rm -f quicksort
