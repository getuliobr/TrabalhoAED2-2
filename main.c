#include <stdio.h>
#include "trie.h"
#include "lista.h"

int main(){
    TRIE* teste = ConstruirDicionario("br.txt");
    Lista* teste1 = TRIE_ChavesComPrefixo(teste, "arg");
    lista_imprimir(teste1);
}