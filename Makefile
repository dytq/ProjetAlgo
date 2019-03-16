all: lib

lib:
	gcc -g -c -fPIC *.c
	ar rcs libgraph.a *.o
