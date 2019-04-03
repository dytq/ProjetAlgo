GCC = gcc
TAR = ar rcs
FLAGS = -g3 -Wall
OPTI = -Ofast
GRAPH = -L. -lgraph
LOC = -I

lib:
	${GCC} -c -fPIC *.c ${OPTI} ${FLAGS}
	${TAR} libgraph.a *.o

compil:
	${GCC} ${LOC} -o graph main.c ${GRAPH} ${OPTI} ${FLAGS}
	
clean:
	rm *.o
	rm *.a 
