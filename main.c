#include <stdio.h>
#include "./Modules/Lista/lista.h"
#include "./Modules/TRIE/trie.h"


int main(){
    TRIE* teste = ConstruirDicionario("br.txt");
    Lista* teste1 = CorrigirOrtografia_Regra1(teste, "rats");
    lista_imprimir(teste1);
}