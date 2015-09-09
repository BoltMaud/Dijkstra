#definition des fonctions selon le choix de l'utilisateur
BH = 0
TAB = 0
ifeq ($(BH),1)
	CFLAGS=-D BH
else
ifeq ($(TAB),1)
	CFLAGS=-D TAB
endif
endif


#vars de compilation
CC=gcc
CFLAGS+=-Wall -Werror -g
DEBUG= -g
EXEC=dijkstra


#vars fichiers
OLIST=main.o liste_ad.o binary_heap.o listechainee.o dijkstra.o binary_search_tree.o tab.o


#edition de liens .o
$(EXEC): $(OLIST)
	$(CC) $(CFLAGS) -o $@ *.o -lm
	make clean


#fichier .o
main.o : main.c liste_ad.h binary_heap.h system.h listechainee.h dijkstra.h
liste_ad.o : liste_ad.c liste_ad.h system.h
binary_heap.o : binary_heap.c binary_heap.h system.h
listechainee.o : listechainee.c listechainee.h system.h
dijkstra.o : dijkstra.c dijkstra.h system.h
binary_search_tree.o : binary_search_tree.c binary_search_tree.h system.h
tab.o : tab.c tab.h system.h

#compilation
%.o :
	$(CC) $(CFLAGS) -c $<

#petits plus qui rendent la vie plus facile
archive :
	tar -cvf SDA_fin.tar.gz *.c *.h  *.pdf makefile

clean :
	rm -f *.o main

