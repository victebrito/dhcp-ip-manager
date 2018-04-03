main: LISTA.o func.o main.o
	gcc LISTA.o func.c main.o -o atualizaIP
main.o: main.c func.h LISTA.h
	gcc -g -c main.c
func.o: func.c func.h LISTA.h
	gcc -g -c func.c
LISTA.o: LISTA.c LISTA.h
	gcc -g -c LISTA.c
