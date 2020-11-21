#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "trie.h"

static void toLower(char* str) {
    for(int i = 0; str[i]; i++){
        str[i] = tolower(str[i]);
    }
}

static TRIE* AT_Criar(){
    TRIE* noh = malloc(sizeof(TRIE));
    int i;
    noh->estado = ATE_LIVRE;
    noh->val = 0;
    noh->tamanho = 0;
    for(i = 0; i < 256; i++){
        noh->filhos[i] = NULL;
    }

    return noh;
}

static void AT_Inserir_I(TRIE **T, unsigned char *chave, int val){
    int i;
    TRIE** aux = T;
    for(i = 0; i <= strlen(chave); i++){
        if(*aux == NULL)
            *aux = AT_Criar();
        if(i == strlen(chave)){
            (*aux)->val = val;
            (*aux)->estado = ATE_OCUPADO;
        }
        aux = &(*aux)->filhos[chave[i]];
    }
    (*T)->tamanho++;

}

TRIE* ConstruirDicionario(char* arq_lista_palavras){
    TRIE* dicionario = NULL;
    AT_Inserir_I(&dicionario, "", 0);
    FILE* dic = fopen( arq_lista_palavras, "r");
    char* palavra = calloc(50, sizeof(char));
    int i = 1;
    while(!feof(dic)){
        fgets(palavra, 50, dic);
        toLower(palavra);
        AT_Inserir_I(&dicionario, palavra, i++);
    }   
    return dicionario;
}

void AT_Imprimir_R(TRIE* T, int nivel, unsigned char c){
    int i;
    for(i = 0; i < nivel; i++)
        printf("-");

    printf("(%c) %d (%c)\n",c, T->val, T->estado == ATE_OCUPADO ? 'O': 'L');

    for(i = 0; i < 255; i++){
        if(T->filhos[i] != NULL)
            AT_Imprimir_R(T->filhos[i], nivel+1, i);
    }
}

void AT_Imprimir(TRIE* T){
    printf("\n");
    AT_Imprimir_R(T, 0, ' ');
}

