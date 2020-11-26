#pragma once
#include "../Lista/lista.h"

typedef enum TRIE_Estado{
    ATE_LIVRE,
    ATE_OCUPADO
} TRIE_ESTADO;

typedef struct TRIE{
    int val;
    int tamanho;
    TRIE_ESTADO estado;
    struct TRIE* filhos[26];
} TRIE;


TRIE* ConstruirDicionario(char* arq_lista_palavras);
void AT_Imprimir(TRIE* T);
Lista* TRIE_ChavesComPrefixo(TRIE * T, char* prefix);
// Lista TRIE_ChavesQueCasam(TRIE *, char* padrao, int n_extras);
char* TRIE_ChaveMaiorPrefixoDe(TRIE* T, char* s);
void CorrigirOrtografia(TRIE* dicionario, char* texto);