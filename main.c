#include <stdio.h>
#include "trie.h"

int main(){
    TRIE* teste = ConstruirDicionario("br.txt");
    AT_Imprimir(teste);
}