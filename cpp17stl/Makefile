CC=g++

CFLAGS=-std=c++17 -Wpedantic

structured_bindings: structured_bindings.cpp
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean

clean:
	rm -f structured_bindings
