#pragma once

typedef enum boolean{false=0, true=1} Boolean;
typedef char* Tipo;


typedef struct no{
    Tipo dado;
    struct no* prox;
    struct no* ant;
}No;

typedef struct{
    No* primeiro;
    No* ultimo;
    int qtde;
}Lista;


Lista* lista_criar();   //Cria lista
void lista_destruir(Lista* l);  //Destroi lista

void lista_inserir(Lista* l, Tipo elemento, int posicao);   // Insere elemento na posição passada por parametro
void lista_inserir_fim(Lista* l, Tipo elemento);            // Insere elemento na ultima posição 

Tipo lista_remover1(Lista* l, int posicao);                     // Remove o elemento da posição passada por parametro
Boolean lista_remover2(Lista* l, int posicao, Tipo* endereco);  // Remove o elemento na posição passada por parametro e coloca no endereço também passado por parametro
Boolean lista_remover_elemento(Lista* l, Tipo elemento);        // Remove o elemento da lista que foi passado por parametro


Boolean lista_buscar(Lista* l, int posicao, Tipo* endereco);    // Busca a palavra na posição e coloca no endereço
Boolean lista_contem(Lista* l, Tipo elemento);                  // Verifica se a Lista contem o elemento
int lista_posicao(Lista* l, Tipo elemento);                     // Retorna a posição do elemento na lista

int lista_tamanho(Lista* l);                                    // Retorna o tamanho da lista
void lista_imprimir(Lista* l);                                  // Imprime a Lista