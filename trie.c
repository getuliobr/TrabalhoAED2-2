#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "trie.h"

#define MAXC 64   

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
    for(i = 0; i < 26; i++){
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

static void inserirDic(TRIE** T, char* arq_lista_palavras) {

    char palavra[MAXC] = "";
    int linha = 1;
    FILE* fp = fopen(arq_lista_palavras, "r");

    while (fgets (palavra, sizeof(palavra), fp)) {
        char et[MAXC] = "";

        if (linha == 1) {
          palavra[strlen(palavra) - 1] = '\0';
        }

        if(linha != 1) {
          sscanf (palavra, "%s", et);
          strcpy(palavra, et);
        }
        printf("%s\n", palavra);
        AT_Inserir_I(T, palavra, linha);
        linha++;
    }

    fclose(fp);
}

TRIE* ConstruirDicionario(char* arq_lista_palavras){
    printf("Abrindo arquivo de dicionario: %s\n", arq_lista_palavras);
    TRIE* dicionario = AT_Criar();
    inserirDic(&dicionario, arq_lista_palavras);

    return dicionario;
}

void AT_Imprimir_R(TRIE* T, int nivel, unsigned char c){
    int i;
    for(i = 0; i < nivel; i++)
        printf("-");
    if(c + 97 == 129) c -= 97;
    printf("(%c) %d (%c)\n", c + 97, T->val, T->estado == ATE_OCUPADO ? 'O': 'L');

    for(i = 0; i < 26; i++){
        if(T->filhos[i] != NULL)
            AT_Imprimir_R(T->filhos[i], nivel+1, i);
    }
}

void AT_Imprimir(TRIE* T){
    printf("\n");
    AT_Imprimir_R(T, 0, ' ');
}

