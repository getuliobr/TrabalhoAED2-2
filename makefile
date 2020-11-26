all: TRIE LISTA
	gcc -g main.c -o main *.o
	rm *.o

TRIE:
	gcc -g -c ./Modules/TRIE/trie.c

LISTA:
	gcc -g -c ./Modules/Lista/lista.c