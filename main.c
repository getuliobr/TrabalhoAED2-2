#include <stdio.h>
#include "./Modules/Lista/lista.h"
#include "./Modules/TRIE/trie.h"

int main(){
    TRIE* teste = ConstruirDicionario("br.txt");
    Lista* teste1 = TRIE_ChavesComPrefixo(teste, "arg");
    lista_imprimir(teste1);
}