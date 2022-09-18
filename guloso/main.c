#include <stdio.h>
#include <stdlib.h>
#include<time.h> // Necessário para o uso da função time()

// Este algoritmo leva em consideração a técnica gulosa, utilizando como base o melhor caminho
// para se chegar ao resultado final, no caso, fazer "velha" no jogo da velha.

typedef struct Matriz
{
    char posicoes[3][3];
}no;

int jogador = 0; // 0: primeiro jogador (X). 1: segundo jogador (O). Ambos são automáticos.
int execucoes = 0; // Controle de quantas vezes foi executado para verificações
int parar = 0;

// Preenche o tabuleiro com o espaço do teclado (32 na tabela ascii), indicando as posições vazias.
no * preencherInicio(){
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

    printf("\nExecucoes: %d\n", execucoes);
    printf("Jogador %d\n\n", jogador);
}

// Funções que verificam se uma linha, coluna ou diagonal atingiu 3X ou 3O
void somaLinhas(char matriz[3][3], int L[3]){
    // Caso alguma linha possua valor 3 ou -3, significa respectivamente que, X ou O ganhou. 
    int i, j;

    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            if(matriz[i][j] == 'X'){
                L[i] = L[i] + 1;
            }
            if(matriz[i][j] == 'O'){
                L[i]--;
            }
        }
    }
}

void somaColunas(char matriz[3][3], int C[3]){
    int i, j;
    
    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            if(matriz[j][i] == 'X'){
                C[i] = C[i] + 1;
            }
            if(matriz[j][i] == 'O'){
                C[i]--;
            }
        }
    }
}

void somaDiagonais(char matriz[3][3], int D[2]){
    int i, j;
    
    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            if(i == j){
                if(matriz[j][i] == 'X'){
                    D[0] = D[0] + 1;
                }
                if(matriz[j][i] == 'O'){
                    D[0]--;
                }
            }
            if((i + j == 2)){
                if(matriz[j][i] == 'X'){
                    D[1] = D[1] + 1;
                }
                if(matriz[j][i] == 'O'){
                    D[1]--;
                }
            }
        }
    }
}

int maior(int LCD[], int tam){
    int i, maior = -10, posMaior;

    for(int i = 0; i < tam; i++){
        if(LCD[i] >= maior){
            posMaior = i;
            maior = LCD[i];
        }
    }

    return posMaior;
}

// Função que atua em casos específicos onde há "empate" sobre onde colocar o X
void aleatorioX(char Matriz[3][3]){
    int linha, coluna;
    srand((unsigned)time(NULL));
    
    do{
        linha = rand() % 3;
        coluna = rand() % 3;
    } while(Matriz[linha][coluna] != 32);
    Matriz[linha][coluna] = 'X';
}

void preencheMatrizLivres(char matriz[3][3], int livres[2][9]){
    // Preenche a matriz livres
    int i, j;
    int auxL = 0, auxC = 0;
    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            if(matriz[i][j] == 32){
                livres[auxL][auxC] = i;
                auxL++;
                livres[auxL][auxC] = j;
                auxC++;
                auxL = 0;
            }else if(matriz[i][j] == 'X'){
                livres[auxL][auxC] = 5;
                auxL++;
                livres[auxL][auxC] = 5;
                auxC++;
                auxL = 0;
            } else {
                livres[auxL][auxC] = -5;
                auxL++;
                livres[auxL][auxC] = -5;
                auxC++;
                auxL = 0;
            }
        }
    }
}

void preenchimentoOInicial(char matriz[3][3]){
    printf("preenchimentoOInicial\n");
    int i, j;
    int linha, coluna;
    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            if(i == 0 && matriz[i][j] == 'X'){
                do {
                    if(j == 0){
                       linha = rand() % 2;
                        coluna = rand() % 2;
                    } else if(j == 1){
                        linha = rand() % 2;
                        coluna = rand() % 3;
                    } else{
                        linha = rand() % 2;
                        coluna = 1 + (rand() % 2);
                    }                       
                } while(matriz[linha][coluna] == 'X');
                matriz[linha][coluna] = 'O';
                ++execucoes;
            } else if(i == 1 && matriz[i][j] == 'X'){
                do {
                    if(j == 0){
                        linha = rand() % 3;
                        coluna = rand() % 2;
                    } else if(j == 1){
                        linha = rand() % 3;
                        coluna = rand() % 3;
                    } else{
                        linha = rand() % 3;
                        coluna = 1 + (rand() % 2);
                    }                       
                } while(matriz[linha][coluna] == 'X');
                matriz[linha][coluna] = 'O';
                ++execucoes;
            } else if(i == 2 && matriz[i][j] == 'X'){
                do {
                    if(j == 0){
                        linha = 1 + (rand() % 2);
                        coluna = rand() % 2;
                    } else if(j == 1){
                        linha = 1 + (rand() % 2);
                        coluna = rand() % 3;
                    } else{
                        linha = 1 + (rand() % 2);
                        coluna = 1 + (rand() % 2);
                    }                       
                } while(matriz[linha][coluna] == 'X');
                matriz[linha][coluna] = 'O';
                ++execucoes;
            } 
        }
    }
}

// Desenvolvimento raciocínio do funcionamento do algoritmo
no * solucao(){
    no * final = NULL;
    int i, j;
    int numVazios = -1;
    int linha, coluna;
    int SL[3] = {0, 0, 0};
    int SC[3] = {0, 0 ,0};
    int SD[3] = {0, 0, 0};
    int maiorL = -10;
    int maiorC = -10;
    int maiorD = -10;
    int livres[2][9]; // Representa uma matriz que mostra como está livre a matriz preenchida após o início do primeiro X e primeira O.
    // CASO ESTEJA OCUPADA POR X É PREENCHIDA COM 5 EM L E C E CASO ESTEJA OCUPADA POR O É PREENCHIDA COM -5 EM L E C.
    // SEGUE O MODELO DA MATRIZ A SEGUIR PARA OS VALORES DE 0 À 6
    /*
         1 | 2 | 3
        -----------
         4 | 5 | 6
        -----------
         O | X | 9
   */
    // ex: X está em 8 e O está em 7
    /* 0 1 2 3 4 5 6  7 8
    L  0 0 0 1 1 1 -5 5 2
    C  0 1 2 0 1 2 -5 5 2
    */

    // Atribui uma posição inicial para começar o jogo.
    srand((unsigned)time(NULL));
    int primLinha = rand() % 3;
    int primColuna = rand() % 3;

    final = preencherInicio();
    final->posicoes[primLinha][primColuna] = 'X';
    ++execucoes;
    imprime(final->posicoes);
    ++jogador;
 
    // Início da lógica para resolver o problema pelo algoritmo guloso visando a vitória do X.
    
    preenchimentoOInicial(final->posicoes);
    imprime(final->posicoes);
    jogador--;

    maiorL = maior(SL, 3);
    maiorC = maior(SC, 3);
    maiorD = maior(SD, 2);
    int LCD[3] = {SL[maiorL], SC[maiorC], SD[maiorD]};
    int maiorLCD = maior(LCD, 3);

    preencheMatrizLivres(final->posicoes, livres);

    while(parar != 1 || execucoes < 9) {
        int SL[3] = {0, 0, 0};
        int SC[3] = {0, 0 ,0};
        int SD[2] = {0, 0};
        somaLinhas(final->posicoes, SL);
        somaColunas(final->posicoes, SC);
        somaDiagonais(final->posicoes, SD);

        maiorL = maior(SL, 3);
        maiorC = maior(SC, 3);
        maiorD = maior(SD, 2);
        // printf("SL[0]: %d\nSL[1]: %d\nSL[2]: %d\n", SL[0], SL[1], SL[2]);
        // printf("SC[0]: %d\nSC[1]: %d\nSC[2]: %d\n", SC[0], SC[1], SC[2]);
        // printf("SD[0]: %d\nSD[1]: %d\n", SD[0], SD[1]);
        int LCD[3] = {SL[maiorL], SC[maiorC], SD[maiorD]};
        maiorLCD = maior(LCD, 3);
        // printf("Pos maior LCD: %d\n", maiorLCD);
        
        if(jogador == 0){
            // Utiliza então, o maior valor da soma dos elementos de linha, coluna e diagonal atribuindo pesos(X = 1 e O = -1) como heurística.
            // for(i = 0; i < 2; i++){
            //     for(j = 0; j < 9; j++){
            //         printf("%d ", livres[i][j]);
            //     }
            //     printf("\n");
            // }
       
            if(maiorLCD  == 2){
                // maiorD == 0 significa que está na diagonal principal e maiorD == 1 na diagonal secundária
                if(maiorD == 0){
                    if((livres[0][0] != 5) && (livres[0][0] != -5)){
                        final->posicoes[livres[0][0]][livres[1][0]] = 'X';
                        preencheMatrizLivres(final->posicoes, livres);
                    } else if((livres[0][4] != 5) && (livres[0][4] != -5)){
                        final->posicoes[livres[0][4]][livres[1][4]] = 'X';
                        preencheMatrizLivres(final->posicoes, livres);
                    } else if((livres[0][8] != 5) && (livres[0][8] != -5)){
                        final->posicoes[livres[0][8]][livres[1][8]] = 'X';
                        preencheMatrizLivres(final->posicoes, livres);
                    } else {
                        aleatorioX(final->posicoes);
                        preencheMatrizLivres(final->posicoes, livres);
                    }
                } else if(maiorD == 1) {
                    if((livres[0][2] != 5) && (livres[0][2] != -5)){
                        final->posicoes[livres[0][2]][livres[1][2]] = 'X';
                        preencheMatrizLivres(final->posicoes, livres);
                    } else if((livres[0][4] != 5) && (livres[0][4] != -5)){
                        final->posicoes[livres[0][4]][livres[1][4]] = 'X';
                        preencheMatrizLivres(final->posicoes, livres);
                    } else if((livres[0][6] != 5) && (livres[0][6] != -5)){
                        final->posicoes[livres[0][6]][livres[1][6]] = 'X';
                        preencheMatrizLivres(final->posicoes, livres);
                    } else {
                        aleatorioX(final->posicoes);
                        preencheMatrizLivres(final->posicoes, livres);
                    }
                }               
            }
            if(maiorLCD == 1){
                // maiorC == 0 significa que está na primeira coluna, maiorC == 1 na segunda coluna e maiorC == 2 na terceira coluna
                if(maiorC == 0){
                    if((livres[0][0] != 5) && (livres[0][0] != -5)){
                        final->posicoes[livres[0][0]][livres[1][0]] = 'X';
                        preencheMatrizLivres(final->posicoes, livres);
                    } else if((livres[0][3] != 5) && (livres[0][3] != -5)){
                        final->posicoes[livres[0][3]][livres[1][3]] = 'X';
                        preencheMatrizLivres(final->posicoes, livres);
                    } else if((livres[0][6] != 5) && (livres[0][6] != -5)){
                        final->posicoes[livres[0][6]][livres[1][6]] = 'X';
                        preencheMatrizLivres(final->posicoes, livres);
                    } else {
                        aleatorioX(final->posicoes);
                        preencheMatrizLivres(final->posicoes, livres);
                    }
                }
                if(maiorC == 1){
                    if((livres[0][1] != 5) && (livres[0][1] != -5)){
                        final->posicoes[livres[0][1]][livres[1][1]] = 'X';
                        preencheMatrizLivres(final->posicoes, livres);
                    } else if((livres[0][4] != 5) && (livres[0][4] != -5)){
                        final->posicoes[livres[0][4]][livres[1][4]] = 'X';
                        preencheMatrizLivres(final->posicoes, livres);
                    } else if((livres[0][7] != 5) && (livres[0][7] != -5)){
                        final->posicoes[livres[0][7]][livres[1][7]] = 'X';
                        preencheMatrizLivres(final->posicoes, livres);
                    } else {
                        aleatorioX(final->posicoes);
                        preencheMatrizLivres(final->posicoes, livres);
                    }
                }
                if(maiorC == 2){
                    if((livres[0][2] != 5) && (livres[0][2] != -5)){
                        final->posicoes[livres[0][2]][livres[1][2]] = 'X';
                        preencheMatrizLivres(final->posicoes, livres);
                    } else if((livres[0][5] != 5) && (livres[0][5] != -5)){
                        final->posicoes[livres[0][5]][livres[1][5]] = 'X';
                        preencheMatrizLivres(final->posicoes, livres);
                    } else if((livres[0][8] != 5) && (livres[0][8] != -5)){
                        final->posicoes[livres[0][8]][livres[1][8]] = 'X';
                        preencheMatrizLivres(final->posicoes, livres);
                    } else {
                        aleatorioX(final->posicoes);
                        preencheMatrizLivres(final->posicoes, livres);
                    }
                }
            }
            if(maiorLCD == 0){
                // maiorL == 0 significa que está na primeira linha, maiorL == 1 na segunda linha e maiorL == 2 na terceira linha
                if(maiorL == 0){
                    if((livres[0][0] != 5) && (livres[0][0] != -5)){
                        final->posicoes[livres[0][0]][livres[1][0]] = 'X';
                        preencheMatrizLivres(final->posicoes, livres);
                    } else if((livres[0][1] != 5) && (livres[0][1] != -5)){
                        final->posicoes[livres[0][1]][livres[1][1]] = 'X';
                        preencheMatrizLivres(final->posicoes, livres);
                    } else if((livres[0][2] != 5) && (livres[0][2] != -5)){
                        final->posicoes[livres[0][2]][livres[1][2]] = 'X';
                        preencheMatrizLivres(final->posicoes, livres);
                    } else {
                        aleatorioX(final->posicoes);
                        preencheMatrizLivres(final->posicoes, livres);
                    }
                }
                if(maiorL == 1){
                    if((livres[0][3] != 5) && (livres[0][3] != -5)){
                        final->posicoes[livres[0][3]][livres[1][3]] = 'X';
                        preencheMatrizLivres(final->posicoes, livres);
                    } else if((livres[0][4] != 5) && (livres[0][4] != -5)){
                        final->posicoes[livres[0][4]][livres[1][4]] = 'X';
                        preencheMatrizLivres(final->posicoes, livres);
                    } else if((livres[0][5] != 5) && (livres[0][5] != -5)){
                        final->posicoes[livres[0][5]][livres[1][5]] = 'X';
                        preencheMatrizLivres(final->posicoes, livres);
                    } else {
                        aleatorioX(final->posicoes);
                        preencheMatrizLivres(final->posicoes, livres);
                    }
                }
                if(maiorL == 2){
                    if((livres[0][6] != 5) && (livres[0][6] != -5)){
                        final->posicoes[livres[0][6]][livres[1][6]] = 'X';
                        preencheMatrizLivres(final->posicoes, livres);
                    } else if((livres[0][7] != 5) && (livres[0][7] != -5)){
                        final->posicoes[livres[0][7]][livres[1][7]] = 'X';
                        preencheMatrizLivres(final->posicoes, livres);
                    } else if((livres[0][8] != 5) && (livres[0][8] != -5)){
                        final->posicoes[livres[0][8]][livres[1][8]] = 'X';
                        preencheMatrizLivres(final->posicoes, livres);
                    } else {
                        aleatorioX(final->posicoes);
                        preencheMatrizLivres(final->posicoes, livres);
                    }
                }
            }
            execucoes++;
        }
        // Atribiu posição aleatória para o O
        if(jogador == 1){
            do{
                linha = rand() % 3;
                coluna = rand() % 3;
            } while(final->posicoes[linha][coluna] != 32);
            final->posicoes[linha][coluna] = 'O';
            preencheMatrizLivres(final->posicoes, livres);
            execucoes++;
        }

        imprime(final->posicoes);

        SL[0] = 0; SL[1] = 0; SL[2] = 0;
        SC[0] = 0; SC[1] = 0; SC[2] = 0;
        SD[0] = 0; SD[1] = 0;
        somaLinhas(final->posicoes, SL);
        somaColunas(final->posicoes, SC);
        somaDiagonais(final->posicoes, SD);
        if(SL[0] == 3 || SL[1] == 3 || SL[2] == 3 || SC[0] == 3 || SC[1] == 3 || SC[2] == 3 || SD[0] == 3 || SD[1] == 3 ||
        SL[0] == -3 || SL[1] == -3 || SL[2] == -3 || SC[0] == -3 || SC[1] == -3 || SC[2] == -3 || SD[0] == -3 || SD[1] == -3){
            parar = 1;
        }

        if(parar == 1){
            return final;
        }

        if(jogador == 0){
            jogador++;
        } else {
            jogador--;
        }

    }    
    
    return final;
}

void main(){
    no *finalizado = NULL;

    finalizado = solucao();
    // imprime(finalizado->posicoes);
    if(jogador == 0){
        printf("O jogador do X venceu! Parabens\n");
    } else if(jogador == 1){
        printf("O jogador da O venceu! Parabens\n");
    } else {
        printf("Deu velha! :/\n");
    }
}