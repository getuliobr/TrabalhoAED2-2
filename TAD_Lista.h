#include <stdio.h>
#include <stdlib.h>

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


Lista* lista_criar();
void lista_destruir(Lista* l);

void lista_inserir(Lista* l, Tipo elemento, int posicao);
void lista_inserir_fim(Lista* l, Tipo elemento);

int* lista_remover1(Lista* l, int posicao);
Boolean lista_remover2(Lista* l, int posicao, Tipo* endereco);
Boolean lista_remover_elemento(Lista* l, Tipo elemento);


Boolean lista_buscar(Lista* l, int posicao, int* endereco);
Boolean lista_contem(Lista* l, Tipo elemento);
int lista_posicao(Lista* l, Tipo elemento);

int lista_tamanho(Lista* l);
void lista_imprimir(Lista* l);

Lista* lista_criar(){
    Lista* l = (Lista*) malloc(sizeof(Lista));
    l->qtde =0 ; 
    l->primeiro = NULL;
    l->ultimo = NULL;
    return l;
}

Lista* lista_destruir(Lista* l){
    No* aux = l->primeiro;
    No* aux2;
    for(int i = 0; i < l->qtde; i++){
        aux2 = aux;
        aux = aux->prox;
        free(aux2);
    }
    free(l);
    return NULL;
}

/*
    CRIA NÓ
                */
No* criaNo(Tipo elemento, No* anterior, No* proximo){
    No* n = (No*) malloc(sizeof(No));
    n->dado = elemento;
    n->ant = anterior;
    n->prox = proximo;
    return n;
}

/*
    RETORNA UM NÓ DE CERTA POSIÇÃO
                                    */
No* getNo(Lista* l, int posicao){
    No* aux;
    if(l->qtde - posicao > posicao){
        aux = l->ultimo;
        for(int i = l->qtde-1; i > posicao; i--){
            aux = aux->ant;
        }
    }
    else if(l->qtde - posicao < posicao){
        aux = l->primeiro;
        for(int i = 0; i < posicao; i++){
            aux = aux->prox;
        }
    }
    return aux;
}

void lista_inserir(Lista* l, Tipo elemento, int posicao){
    if(l->qtde == 0){
        No* n = criaNo(elemento,NULL,NULL);
        l->primeiro = n;
        l->ultimo = n;
        l->qtde++;
    }
    else if(posicao == 0){
        No* n = criaNo(elemento,NULL,l->primeiro);
        l->primeiro->ant = n;
        l->primeiro = n;
        l->qtde++;
    }
    else if(posicao == l->qtde){
        No* n = criaNo(elemento,l->ultimo,NULL);
        l->ultimo->prox = n;
        l->ultimo = n;
        l->qtde++;
    }
    else if(posicao > 0 && posicao < l->qtde){
        No* pos = getNo(l,posicao);
        No* n = criaNo(elemento,pos->ant,pos);
        pos->ant->prox = n;
        pos->ant = n;
        l->qtde++;
    }
}

void lista_inserir_fim(Lista* l, Tipo elemento){
    if(l->qtde == 0){
        No* n = criaNo(elemento,NULL,NULL);
        l->qtde++;
        l->primeiro = l->ultimo = n;
    }
    else{
        No* n = criaNo(elemento,l->ultimo,NULL);
        l->ultimo->prox = n;
        l->ultimo = n;
        l->qtde++;
    }
}

int* lista_remover1(Lista* l, int posicao){
    int* elemento = (int*) malloc(sizeof(int));
    if(l->qtde == 1){
        *elemento = l->primeiro->dado;
        l->qtde--;
        l->primeiro = l->ultimo = NULL;
    }
    else if(posicao == 0){
        *elemento = l->primeiro->dado;
        l->qtde--;
        No* aux = l->primeiro;
        aux->prox->ant = NULL;
        l->primeiro = l->primeiro->prox;
        free(aux);
    }
    else if(posicao == l->qtde - 1){
        *elemento = l->primeiro->dado;
        l->qtde--;
        No* aux = l->ultimo;
        aux->ant->prox = NULL;
        l->ultimo = l->ultimo->ant;
        free(aux);
    }
    else if(posicao > 0 && posicao < l->qtde - 1){
        No* aux = getNo(l,posicao);
        aux->ant->prox = aux->prox;
        aux->prox->ant = aux->ant;
        *elemento = aux->dado;
        l->qtde--;
        free(aux);
    }
}

Boolean lista_remover2(Lista* l, int posicao, Tipo* endereco){
    if(l == NULL)   return false;
    
    if(l->qtde == 1){
        *endereco = l->primeiro->dado;
        l->qtde--;
        l->primeiro = l->ultimo = NULL;
    }
    else if(posicao == 0){
        *endereco = l->primeiro->dado;
        l->qtde--;
        No* aux = l->primeiro;
        aux->prox->ant = NULL;
        l->primeiro = l->primeiro->prox;
        free(aux);
    }
    else if(posicao == l->qtde - 1){
        *endereco = l->primeiro->dado;
        l->qtde--;
        No* aux = l->ultimo;
        aux->ant->prox = NULL;
        l->ultimo = l->ultimo->ant;
        free(aux);
    }
    else if(posicao > 0 && posicao < l->qtde - 1){
        No* aux = getNo(l,posicao);
        aux->ant->prox = aux->prox;
        aux->prox->ant = aux->ant;
        *endereco = aux->dado;
        l->qtde--;
        free(aux);
    }
    return true;
}

Boolean lista_remover_elemento(Lista* l, Tipo elemento){
    if(l == NULL)   return false;

    No* aux = l->primeiro;
    int flag = 0;
    int i;
    for(i = 0; i < l->qtde; i++){
        if(aux->dado == elemento){
            flag++;
            break;
        }
        aux = aux->prox;
    }
    if(flag == 0)
        return false;
    
    if(i == 0){
        aux->prox->ant = NULL;
        l->primeiro = aux->prox;
    }
    else if(i == l->qtde-1){
        aux->ant->prox = NULL;
        l->ultimo = aux->ant;
    }
    else{
        aux->ant->prox = aux->prox;
        aux->prox->ant = aux->ant;
    }
    l->qtde--;
    free(aux);
    return true;
}

Boolean lista_buscar(Lista* l, int posicao, int* endereco){
    if(l == NULL)   return false;
    if(posicao > l->qtde-1 || posicao < 0) return false;
    if(l->qtde == 0)    return false;

    if(posicao == 0)
        *endereco = l->primeiro->dado;
    else if(posicao == l->qtde-1)
        *endereco = l->ultimo->dado;
    else{
        No* aux = getNo(l,posicao);
        *endereco = aux->dado;
    }
    return true;
}

Boolean lista_contem(Lista* l, Tipo elemento){
    if(l == NULL)   return false;
    if(l->qtde == 0)    return false;

    No* aux = l->primeiro;
    for(int i = 0; i < l->qtde; i++){
        if(aux->dado == elemento)
            return true;
        aux = aux->prox;
    }
    return false;
}

int lista_posicao(Lista* l, Tipo elemento){
    No* aux = l->primeiro;
    for(int i = 0 ; i < l->qtde; i++){
        if(aux->dado == elemento)   return i;
        aux = aux->prox;
    }
    return -1;
}

int lista_tamanho(Lista *l){
    return l->qtde;
}
