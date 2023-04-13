all: tree.o
	gcc tree.o main.c -o main.exe

tree.o: tree.h
	gcc -c tree.c
