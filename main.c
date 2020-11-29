#include <stdio.h>
#include <time.h>
#include "./Modules/Lista/lista.h"
#include "./Modules/TRIE/trie.h"


int main(int argc, char** argv){
    TRIE* dicionario = ConstruirDicionario("br.txt");
    clock_t t = clock();
    CorrigirOrtografia(dicionario, argv[1]);
    t = clock() - t;
    printf("Tempo de execucao: %f\n", (((float)t)/CLOCKS_PER_SEC));
}