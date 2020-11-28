#include <stdio.h>
#include "./Modules/Lista/lista.h"
#include "./Modules/TRIE/trie.h"


int main(){
    TRIE* dicionario = ConstruirDicionario("br.txt");
    printf("%d\n", noDicionario(dicionario, "rats"));
    CorrigirOrtografia(dicionario, "teste.txt");
}