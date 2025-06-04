#include <stdio.h>
#include <stdlib.h> 

#define TAM 10
#define TAM_NAVIO 3
#define TAM_HABILIDADE 5  // Tamanho fixo para as matrizes de habilidade
#define AFETADO 5          // Valor para indicar área de efeito

// Função para imprimir o tabuleiro com cabeçalho
void imprimirTabuleiro(int tabuleiro[TAM][TAM]) {
    printf("    ");
    for (int j = 0; j < TAM; j++) {
        printf("%c ", 'A' + j);
    }
    printf("\n");

    for (int i = 0; i < TAM; i++) {
        printf("%2d  ", i + 1);
        for (int j = 0; j < TAM; j++) {
            if (tabuleiro[i][j] == 0)
                printf("~ ");
            else if (tabuleiro[i][j] == 3)
                printf("N ");
            else if (tabuleiro[i][j] == AFETADO)
                printf("* ");
            else
                printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Gera matriz Cone (triângulo para baixo)
void gerarCone(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            int meio = TAM_HABILIDADE / 2;
            if (j >= meio - i && j <= meio + i) {
                matriz[i][j] = 1;
            } else {
                matriz[i][j] = 0;
            }
        }
    }
}

// Gera matriz Cruz
void gerarCruz(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int meio = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (i == meio || j == meio) {
                matriz[i][j] = 1;
            } else {
                matriz[i][j] = 0;
            }
        }
    }
}

// Gera matriz Octaedro (losango)
void gerarOctaedro(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int meio = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (abs(i - meio) + abs(j - meio) <= meio) {
                matriz[i][j] = 1;
            } else {
                matriz[i][j] = 0;
            }
        }
    }
}

// Sobrepõe a habilidade no tabuleiro, respeitando limites
void aplicarHabilidade(int tabuleiro[TAM][TAM], int habilidade[TAM_HABILIDADE][TAM_HABILIDADE], int origem_i, int origem_j) {
    int offset = TAM_HABILIDADE / 2;

    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (habilidade[i][j] == 1) {
                int ti = origem_i + (i - offset);
                int tj = origem_j + (j - offset);

                if (ti >= 0 && ti < TAM && tj >= 0 && tj < TAM) {
                    if (tabuleiro[ti][tj] == 0)  // Mantém navios visíveis
                        tabuleiro[ti][tj] = AFETADO;
                }
            }
        }
    }
}

int main() {
    int tabuleiro[TAM][TAM] = {0};

    // Coordenadas dos navios
    int linha_h1 = 1, col_h1 = 1;
    int linha_v1 = 4, col_v1 = 6;
    int linha_diag1 = 0, col_diag1 = 0;
    int linha_diag2 = 0, col_diag2 = 9;

    // Navio horizontal
    for (int i = 0; i < TAM_NAVIO; i++)
        tabuleiro[linha_h1][col_h1 + i] = 3;

    // Navio vertical
    for (int i = 0; i < TAM_NAVIO; i++)
        tabuleiro[linha_v1 + i][col_v1] = 3;

    // Diagonal principal
    for (int i = 0; i < TAM_NAVIO; i++)
        tabuleiro[linha_diag1 + i][col_diag1 + i] = 3;

    // Diagonal inversa
    for (int i = 0; i < TAM_NAVIO; i++)
        tabuleiro[linha_diag2 + i][col_diag2 - i] = 3;

    // Criar matriz de habilidade
    int cone[TAM_HABILIDADE][TAM_HABILIDADE];
    int cruz[TAM_HABILIDADE][TAM_HABILIDADE];
    int octaedro[TAM_HABILIDADE][TAM_HABILIDADE];

    gerarCone(cone);
    gerarCruz(cruz);
    gerarOctaedro(octaedro);

    // Aplicar habilidades
    aplicarHabilidade(tabuleiro, cone, 2, 2);       // Cone em (2,2)
    aplicarHabilidade(tabuleiro, cruz, 5, 5);       // Cruz em (5,5)
    aplicarHabilidade(tabuleiro, octaedro, 7, 7);   // Octaedro em (7,7)

    // Mostrar resultado final
    printf("\n=== TABULEIRO FINAL ===\n");
    imprimirTabuleiro(tabuleiro);

    return 0;
}
