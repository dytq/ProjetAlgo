# Evite conflit:
.PHONY: all lib compil clean

# Constantes:
WARN = -Wall
OPTIM = -g3 -Ofast
GCC = @gcc
MSG = @echo compilation en cours: création de $@
FLAME = -std=c99 -O2 -ffast-math flame.c -lm -lX11
# all
all: graph main.o affiche.o graph.o connexe.o routage.o flame.o moteur_graphique.o clean

# Run:
run: 
	@echo -n lancement du programme:  
	./graph 
	@echo fin de programme:
	
# Edition de lien du programme principal
graph: main.o graph.o routage.o connexe.o affiche.o moteur_graphique.o
	${GCC} -o $@ $^ ${OPTIM} ${WARN} ${FLAME}
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
	
flame.o: flame.c *.h
	${GCC} -c ${OPTIM} ${WARN} $*.c
	${MSG}

moteur_graphique.o: moteur_graphique.c *.h
	${GCC} -c ${OPTIM} ${WARN} $*.c
	${MSG}

# Netoyage des fichiers
clean:
	@echo netoyage des données supression de: *.o
	@rm *.o
test:
	
