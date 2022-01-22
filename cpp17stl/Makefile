CC=g++

CFLAGS=-std=c++17 -Wpedantic

all: structured_bindings\
	 scope_limit

.PHONY: all

structured_bindings: structured_bindings.cpp
	$(CC) $(CFLAGS) -o $@ $^

scope_limit: scope_limit.cpp
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean

clean:
	rm -f structured_bindings\
		  scope_limit
