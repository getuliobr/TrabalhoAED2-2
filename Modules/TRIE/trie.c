#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "trie.h"

#define MAXC 30 

static int mappedChar(int chr) {
    return chr % 'a';
}

static void toLower(char* str) {  // Transforma a palavra para letra minuscula
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
    int maiorPalavra = 0;
    while (fgets (palavra, sizeof(palavra), fp)) { //Busca cada palavra do dicionario e insere na Trie
        char buffer[MAXC] = "";

        if (linha == 1) {
          palavra[strlen(palavra) - 1] = '\0';
        }

        if(linha != 1) {
          sscanf (palavra, "%s", buffer);
          strcpy(palavra, buffer);
        }

        toLower(palavra);
        if(strlen(palavra) > maiorPalavra) maiorPalavra = strlen(palavra);
        AT_Inserir(T, palavra, linha);
        linha++;
    }
    printf("Terminei de ler o arquivo de dicionario e escrevi %d palavras na TRIE\nA maior palavra tinha %d caracteres\n", linha, maiorPalavra);
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
            lista_inserir_fim(retorno, prefix); // Caso ache uma palavra com o prefixo recebido insere na lista chamada por parametro
        }

        int tam_prefix = strlen(prefix);            
        char* aux = (char*) malloc(tam_prefix + 2); // Cria uma copia do prefixo com 1 letra a mais
        strcpy(aux, prefix);

        for(i = 0; i < 26; i++) {
            if(T->filhos[i] != NULL) {               // Procura as letras seguintes do prefixo
                aux[tam_prefix] = 'a'+i;            // Caso ache, coloca a letra seguinte na cópia do prefixo e procura a próxima
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
    char* strAux = (char*) malloc(strlen(prefix) + 1);      //Cria uma copia do prefixo
    strcpy(strAux, prefix);

    for(i = 0; i < tam; i++) {
        aux = aux->filhos[mappedChar(prefix[i])]; // Redireciona a Trie para onde está a ultima letra do prefixo  
        if(aux == NULL) return palavras;
    }
    Busca_Palavra_Prefixo(aux, strAux, palavras); // Procura palavras com o prefixo

    return palavras;
}

void Busca_Palavras_que_Casam(TRIE* T, char* padrao, int nivel, int sem_extra, Lista* l){
    int i;
    if(T != NULL){
        if(nivel > strlen(padrao)) return; // Condição de parada caso a busca ultrapasse o tamanho da palavra + n_extras
        if(nivel > sem_extra && nivel <= strlen(padrao) && T->estado == ATE_OCUPADO) { // Insere a palavra na lista caso ache
            char* toInsert = (char*) malloc(nivel + 1);
            memcpy(toInsert, padrao, nivel);
            toInsert[nivel] = '\0';
            lista_inserir_fim(l, toInsert);
            free(toInsert);
        }

        char *aux = malloc(strlen(padrao)+1);               //Cria cópia da chave
        strcpy(aux, padrao);                
        aux[strlen(padrao)] = '\0';

        if(padrao[nivel] != '*'){   //Caso não seja o coringa, procura a letra seguinte
            Busca_Palavras_que_Casam(T->filhos[mappedChar(padrao[nivel])], aux, nivel+1, sem_extra, l);
        }
        else{                       //Caso seja o coringa procura em todas as 26 chaves
            for(i = 0; i < 26; i++){
                if(T->filhos[i] != NULL){
                    aux[nivel] = 'a'+i;
                    Busca_Palavras_que_Casam(T->filhos[i], aux, nivel+1, sem_extra, l);
                }
            }
        }
        free(aux);
    }
}


Lista* TRIE_ChavesQueCasam(TRIE *T, char* padrao, int n_extras){
    int i;
    int tam = n_extras == 0 ? strlen(padrao)+1: strlen(padrao)+n_extras+1;
    char* aux = malloc(tam);
    strcpy(aux, padrao);    
    for(i = strlen(padrao); i < tam; i++){  //Insere coringas extras na palavra 
        aux[i] = '*';
    }
    aux[tam-1] = '\0';
    Lista* palavras = lista_criar();
    Busca_Palavras_que_Casam(T, aux, 0, strlen(padrao)-1, palavras);
    return palavras;
}

char* TRIE_ChaveMaiorPrefixoDe(TRIE* T, char* s){
    Lista* chaves = lista_criar();
    int tam = strlen(s);
    int currPos = 0;
    char* maiorChave = (char*) malloc(tam + 1);
    maiorChave[0] = '\0';
    TRIE* aux = T;
    for(int i = 0; i < tam; i++) {
        if(aux->estado == ATE_OCUPADO) lista_inserir_fim(chaves, maiorChave); // Insere todos os prefixos encontrados até o final
        if(aux->filhos[mappedChar(s[i])] == NULL) break;
        maiorChave[currPos++] = s[i];
        maiorChave[currPos] = '\0';
        aux = aux->filhos[mappedChar(s[i])];
    }
    if(chaves->ultimo == NULL) return NULL;         // Caso não encontre nenhum retorna NULL
    char* toCopy = (char*)chaves->ultimo->dado;     // Caso encontre, retorna o ultimo elemento inserido da lista
    strcpy(maiorChave, toCopy);
    lista_destruir(chaves);
    return maiorChave;
}

static void inserir_dic(TRIE** dicionario, Lista* l){
    int j = l->qtde;
    char* aux;
    for(int i = 0; i < j; i++){
        lista_remover2(l, 0, &aux);         // Remove a primeira palavra da lista
        AT_Inserir(dicionario, aux, i);     // Insere no dicionario
        free(aux);
    }
}

static void CorrigirOrtografia_Regra1(TRIE* dicionario, TRIE* entrada, char* palavra) {
    char* aux = malloc(strlen(palavra));
    for(int i = 0; i < strlen(palavra); i++){ // Troca letra por letra pelo coringa e faz a busca em cada caso retornando uma TRIE
        strcpy(aux, palavra);
        aux[i] = '*';
        Lista* listaAux = TRIE_ChavesQueCasam(dicionario, aux, 0);
        inserir_dic(&entrada, listaAux);
        lista_destruir(listaAux);
    }
}

static void CorrigirOrtografia_Regra2(TRIE* dicionario, TRIE* entrada, char* palavra) {
    if(strlen(palavra) <= 5) return;
    // So fazemos com n-3, porque n-2 ja esta incluido.
    // Exemplo: saladq, sala é prefixo de saladq, que é prefixo de salad, ou seja,
    // tudo que encontrar em salad vai ser encontrado por sala.
    int n = strlen(palavra); // Contar o \0
    char* aux = (char*) malloc(n);
    strcpy(aux, palavra);
    aux[n - 3] = '\0';
    Lista* out = TRIE_ChavesComPrefixo(dicionario, aux); // Procura os prefixos
    inserir_dic(&entrada, out); // Insere na trie passada por parametro
    free(aux);
    lista_destruir(out);
}

static void CorrigirOrtografia_Regra3(TRIE* dicionario, TRIE* entrada, char* palavra) {
    char* out = TRIE_ChaveMaiorPrefixoDe(dicionario, palavra); // Encontra o maior prefixo
    if(out == NULL) return;
    AT_Inserir(&entrada, out, entrada->tamanho);// Insere na trie passada por parametro
    free(out);
}

static Lista* CorrigirOrtografia_Regra4(TRIE* dicionario, TRIE* entrada, char* palavra) {
    //Junção da regra 1 e 3
    TRIE* novaTrie = AT_Criar();
    CorrigirOrtografia_Regra1(dicionario, novaTrie, palavra);
    CorrigirOrtografia_Regra2(dicionario, novaTrie, palavra);
    CorrigirOrtografia_Regra3(dicionario, novaTrie, palavra);

    return TRIE_ChavesQueCasam(novaTrie, "*", 50);
}

static int checarFiltro(char ch, char* filtro) { // Função para retirar pontuações do texto
    for(int i = 0; i < strlen(filtro); i++)
        if(ch == filtro[i] || ch == EOF)
            return 1;
    return 0;
}

int noDicionario(TRIE* dicionario, char* palavra) { // Checa se a palavra está no dicionario
    TRIE* aux = dicionario;
    int tamanho = strlen(palavra);
    for(int i = 0; i < tamanho; i++) {
        aux = aux->filhos[mappedChar(palavra[i])];
        if(aux == NULL) return 0;
    }
    return 1;
}

static void Lista_Organiza(Lista** entrada){ // Organiza a Lista de alfabética e colocando as palavras maiores primeiro
    Lista* retorno  = lista_criar();
    int qtde = (*entrada)->qtde;

    No* aux = (*entrada)->primeiro;
    int tamMaior = strlen(aux->dado);
    char* maior;

    int proximo;
    int tam_proximo;
    char* proximo_char;

    for(int i = 0; i < qtde; i++) {
    } 

    for(int i = 0; i < tam; i++){
        aux = (*entrada)->primeiro;
        proximo = 0;
        proximo_char = aux->dado;
        tam_proximo = strlen(aux->dado);
        aux = aux->prox;
        for(int j = 1; j < (*entrada)->qtde; j++){
            if(strlen(aux->dado) > tam_proximo){
                proximo = j;
                tam_proximo = strlen(aux->dado);
                proximo_char = aux->dado;
            }
            aux = aux->prox;
        }
        lista_inserir_fim(retorno, proximo_char);
        lista_remover1(*entrada, proximo);
    }
    lista_destruir(*entrada);
    *entrada = retorno;
}

void CorrigirOrtografia(TRIE* dicionario, char* texto){
    int qtd_palavras = 0;                   // Caso de teste
    int qtd_palavras_incorretas = 0;        // Caso de teste
    int qtd_sugestoes = 0;                  // Caso de teste

    FILE* arq = fopen(texto, "r");
    int size = fseek(arq, 0L, SEEK_END);
    rewind(arq);

    char* filtro = " 1234567890(),.!?:;\"_-\n";

    char ch;
    char* palavra = (char*) malloc(MAXC);

    int pos = 0;
    while (1) {
        ch = fgetc(arq);
        if(checarFiltro(ch, filtro)) { //Filtra a palavra retirando as pontuações e números
            palavra[pos] = '\0';
            if(strlen(palavra)) qtd_palavras++; // Verifica caso a palavra não seja uma pontuação
            toLower(palavra);                   // Coloca a palavra em minusculo
            if(!noDicionario(dicionario, palavra)) {
                TRIE* trieEntrada = AT_Criar();
                Lista* sugestoes = CorrigirOrtografia_Regra4(dicionario, trieEntrada, palavra);
                Lista_Organiza(&sugestoes);
                printf("palavra nao esta no dicionario :  %s\nsugestoes :\n", palavra);
                lista_imprimir(sugestoes);
                qtd_palavras_incorretas++;
                qtd_sugestoes += sugestoes->qtde;
            }
            pos = 0;
            if(ch == EOF){ // Caso chegue no final do arquivo, imprime os resultados dos testes e fecha a função
                printf("Total de palavras : %d\n", qtd_palavras);
                printf("Total de palavras incorretas : %d\n", qtd_palavras_incorretas);
                printf("Media de Sugestoes por palavra incorreta : %.3f\n", (float)qtd_sugestoes/qtd_palavras_incorretas);
                return;
            }
            continue;
        } else {
            palavra[pos++] = ch;
        }
    }
}