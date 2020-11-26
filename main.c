#include <stdio.h>
#include "./Modules/Lista/lista.h"
#include "./Modules/TRIE/trie.h"

int main(){
    TRIE* teste = ConstruirDicionario("br.txt");
    Lista* teste1 = TRIE_ChavesQueCasam(teste, "ca**o", 0);
    lista_imprimir(teste1);
}