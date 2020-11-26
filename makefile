all: TRIE LISTA
	gcc -g main.c -o main *.o
	rm *.o

TRIE:
	gcc -g -c trie.c

LISTA:
	gcc -g -c lista.c