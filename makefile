main: main.o arbol.o
	gcc main.o arbol.o -o main

main.o: main.c arbol.h
	gcc -c main.c

arbol.o: arbol.c arbol.h
	gcc -c arbol.c

