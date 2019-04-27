# Evite conflit:
.PHONY: all lib compil clean

# Constantes:
WARN = -Wall
OPTIM = -g3 -Ofast
GCC = @gcc
MSG = @echo compilation en cours: création de $@

# all
all: graph main.o affiche.o graph.o connexe.o routage.o input.o clean

# Run:
run: 
	@echo -n lancement du programme:  
	./graph 
	@echo fin de programme:
	
# Edition de lien du programme principal
graph: main.o graph.o routage.o connexe.o affiche.o input.o
	${GCC} -o $@ $^ ${OPTIM} ${WARN}
	${MSG}: fichier executable

# Compilation du programme principal
main.o: main.c *.h
	${GCC} -c ${OPTIM} ${WARN} $*.c
	${MSG}

# Compilation des fichiers de gestions du programme
affiche.o: affiche.c *.h
	${GCC} -c ${OPTIM} ${WARN} $*.c
	${MSG}

graph.o: graph.c *.h
	${GCC} -c ${OPTIM} ${WARN} $*.c
	${MSG}
	
connexe.o: connexe.c *.h
	${GCC} -c ${OPTIM} ${WARN} $*.c
	${MSG}
	
routage.o: routage.c *.h
	${GCC} -c ${OPTIM} ${WARN} $*.c
	${MSG}
	
input.o: input.c *.h
	${GCC} -c ${OPTIM} ${WARN} $*.c
	${MSG}
	
# Netoyage des fichiers
clean:
	@echo netoyage des données supression de: *.o
	@rm *.o
