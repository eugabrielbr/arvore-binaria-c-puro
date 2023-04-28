#Autores: Gabriel Silva dos Santos (22211293) e
#Componente curricular: Estrutura de dados (EXA 806)
#Concluido em: 28/04/2023

all: tree.o
	gcc tree.o main.c -o main.exe

tree.o: tree.h
	gcc -c tree.c
