#include <stdio.h>

#define TAM 10
#define TAM_NAVIO 3

int main() {
    int tabuleiro[TAM][TAM] = {0};

    // Coordenadas dos navios
    int linha_navio_h = 2, coluna_navio_h = 3; // Navio horizontal
    int linha_navio_v = 5, coluna_navio_v = 7; // Navio vertical

    // Posiciona navio horizontal
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linha_navio_h][coluna_navio_h + i] = 3;
    }

    // Posiciona navio vertical
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linha_navio_v + i][coluna_navio_v] = 3;
    }

    // Cabeçalho das colunas (A-J)
    printf("    ");
    for (int j = 0; j < TAM; j++) {
        printf("%c ", 'A' + j);
    }
    printf("\n");

    // Exibição do tabuleiro com números nas linhas
    for (int i = 0; i < TAM; i++) {
        printf("%2d  ", i + 1);
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}
