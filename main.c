#include <stdio.h>
#include <stdlib.h>

// Este algoritmo leva em consideração a técnica gulosa, utilizando como base o melhor caminho
// para se chegar ao resultado final, no caso, fazer "velha" no jogo da velha.

typedef struct Matriz
{
    char posicoes[3][3];
    struct Matriz *cim;
    struct Matriz *dir;
    struct Matriz *bai;
    struct Matriz *esq;
}no;

int jogador = 0; // 0: primeiro jogador. 1: segundo jogador. Ambos são automáticos.

// Preenche o tabuleiro com espaço (32 na tabela ascii), indicando as posições vazias.
no * preencher(){
    no *inicial = NULL;
    inicial = (no *)malloc(sizeof(no));
    if (inicial == NULL)
        return NULL;

    int i, j;

    for (i = 0; i < 3; i++){
        for (j = 0; j < 3; j++){
            inicial->posicoes[i][j] = 32;
        }
    }

    inicial->cim = NULL;
    inicial->dir = NULL;
    inicial->bai = NULL;
    inicial->esq = NULL;    

    return inicial;
}

// Imprime a matriz recebida
void imprime(char matriz[3][3]){
    int i, j;
    
    printf("\n");

    for (i = 0; i < 3; i++){
        for (j = 0; j < 3; j++){
            printf(" %c ", matriz[i][j]);
            if(j != 2){
                printf("|");
            }
        }
        if(i != 2){
            printf("\n-----------\n");
        }
    }

    printf("\n");
}

void main(){
    no *inicial = NULL;
    char matriz[3][3];

    inicial = preencher();
    imprime(inicial->posicoes);
}