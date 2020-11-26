#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "trie.h"

#define MAXC 64   

static int mappedChar(int chr) {
    return chr % 'a';
}

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

static void AT_Inserir_R(TRIE **T, unsigned char *chave, int val, int n, int p) {
    if(*T == NULL) {
        *T = AT_Criar();
    }
    if(p == n) {
        (*T)->val = val;
        (*T)->estado = ATE_OCUPADO;
        return;
    }
    AT_Inserir_R(&(*T)->filhos[mappedChar(chave[p])], chave, val, n, p+1);    
}

static void AT_Inserir(TRIE **T, unsigned char *chave, int val) {
    AT_Inserir_R(T, chave, val, strlen(chave), 0);   
    (*T)->tamanho++; 
}

static void inserirDic(TRIE** T, char* arq_lista_palavras) {

    char palavra[MAXC] = "";
    int linha = 1;
    FILE* fp = fopen(arq_lista_palavras, "r");

    while (fgets (palavra, sizeof(palavra), fp)) {
        char buffer[MAXC] = "";

        if (linha == 1) {
          palavra[strlen(palavra) - 1] = '\0';
        }

        if(linha != 1) {
          sscanf (palavra, "%s", buffer);
          strcpy(palavra, buffer);
        }

        toLower(palavra);
        AT_Inserir(T, palavra, linha);
        linha++;
    }
    printf("Terminei de ler o arquivo de dicionario e escrevi %d palavras na TRIE\n", linha);
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
    AT_Imprimir_R(T, 0, ' ');
}

void Busca_Palavra_Prefixo(TRIE *T, char* prefix, Lista* retorno){
    int i;
    if(T != NULL){
        if(T->estado == ATE_OCUPADO) {
            lista_inserir_fim(retorno, prefix);
        }

        int tam_prefix = strlen(prefix);
        char* aux = (char*) malloc(tam_prefix + 2);
        strcpy(aux, prefix);

        for(i = 0; i < 26; i++){
            if(T->filhos[i] != NULL){
                aux[tam_prefix] = 'a'+i;
                aux[tam_prefix+1] = '\0';
                Busca_Palavra_Prefixo(T->filhos[i], aux, retorno);
            }
        }
        free(aux);
    }
}

Lista* TRIE_ChavesComPrefixo(TRIE * T, char* prefix){
    int i;
    int tam = strlen(prefix);
    TRIE* aux = T;
    Lista* palavras = lista_criar();
    char* strAux = (char*) malloc(strlen(prefix) + 1);
    strcpy(strAux, prefix);
    for(i = 0; i < tam; i++)
        aux = aux->filhos[mappedChar(prefix[i])];
    Busca_Palavra_Prefixo(aux, strAux, palavras);

    return palavras;
}