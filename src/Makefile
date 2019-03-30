all: lib compil

lib:
	gcc -g -c -fPIC *.c
	ar rcs libgraph.a *.o

compil:
	gcc -I. -o graph main.c -L. -lgraph -g3
