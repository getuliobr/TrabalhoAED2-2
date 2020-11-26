#include <stdio.h>
#include "./Modules/Lista/lista.h"
#include "./Modules/TRIE/trie.h"

int main(){
    TRIE* teste = ConstruirDicionario("br.txt");
    char* teste1 = TRIE_ChaveMaiorPrefixoDe(teste, "agulhadora");
    printf("%s\n",teste1);
}