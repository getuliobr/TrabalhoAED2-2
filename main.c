#include <stdio.h>
#include "trie.h"
#include "TAD_Lista.h"

int main(){
    TRIE* teste = ConstruirDicionario("br.txt");
    Lista* teste1 = TRIE_ChavesComPrefixo(teste, "ar");
    lista_imprimir(teste1);
}