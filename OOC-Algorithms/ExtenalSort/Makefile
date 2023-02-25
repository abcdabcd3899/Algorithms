.PHONY: all clean
.DEFAULT_GOAL := all

CFLAGS=-O3 -std=c++11 -g

output = test

all: main

main: ./ExtenalSort.cpp
	g++ $(CFLAGS) -o test ./ExtenalSort.cpp

clean:
	rm $(output)
