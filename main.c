#include <stdio.h>
#include "./Modules/Lista/lista.h"
#include "./Modules/TRIE/trie.h"


int main(){
    TRIE* dicionario = ConstruirDicionario("br.txt");
    CorrigirOrtografia(dicionario, "teste.txt");
}