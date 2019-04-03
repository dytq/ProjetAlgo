GCC = gcc
TAR = ar rcs
FLAGS = -g3 -Wall
OPTI = -Ofast
GRAPH = -I. -L. -lgraph

all: lib compil

lib:
	${GCC} -c -fPIC *.c ${OPTI} ${FLAGS}
	${TAR} libgraph.a *.o

compil:
	${GCC} -o graph main.c ${GRAPH} ${OPTI} ${FLAGS}
	
clean:
	rm *.o
	rm *.a 
