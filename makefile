all: TRIE
	gcc -g main.c -o main *.o
	rm *.o

TRIE:
	gcc -g -c trie.c