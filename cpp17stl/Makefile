CC=g++

CFLAGS=-std=c++17 -Wpedantic

all: structured_bindings\
	 scope_limit \
	 vector_item_removal \
	 vector_item_removal_2 \
	 vector_item_removal_3 \
	 lambdas

.PHONY: all

structured_bindings: structured_bindings.cpp
	$(CC) $(CFLAGS) -o $@ $^

scope_limit: scope_limit.cpp
	$(CC) $(CFLAGS) -o $@ $^

vector_item_removal: vector_item_removal.cpp
	$(CC) $(CFLAGS) -o $@ $^

vector_item_removal_2: vector_item_removal_2.cpp
	$(CC) $(CFLAGS) -o $@ $^

vector_item_removal_3: vector_item_removal_3.cpp
	$(CC) $(CFLAGS) -o $@ $^

lambdas: lambdas.cpp
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean

clean:
	rm -f structured_bindings\
		  scope_limit\
		  vector_item_removal\
		  vector_item_removal_2\
		  vector_item_removal_3\
		  lambdas
