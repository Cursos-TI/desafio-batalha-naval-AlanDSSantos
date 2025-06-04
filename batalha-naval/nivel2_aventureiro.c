#include <stdio.h>

#define TAM 10
#define TAM_NAVIO 3

// Função para verificar se o navio pode ser posicionado sem sair do tabuleiro e sem sobreposição
int podePosicionar(int tabuleiro[TAM][TAM], int linha, int coluna, char direcao) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        int l = linha, c = coluna;
        switch (direcao) {
            case 'H': c += i; break;               // horizontal: aumenta coluna
            case 'V': l += i; break;               // vertical: aumenta linha
            case 'D': l += i; c += i; break;       // diagonal principal: linha e coluna aumentam
            case 'I': l += i; c -= i; break;       // diagonal inversa: linha aumenta, coluna diminui
            default: return 0;                     // direção inválida
        }
        // Verifica limites do tabuleiro
        if (l < 0 || l >= TAM || c < 0 || c >= TAM) {
            return 0; // fora do tabuleiro
        }
        // Verifica se a posição já está ocupada
        if (tabuleiro[l][c] != 0) {
            return 0; // posição ocupada
        }
    }
    return 1; // pode posicionar
}

// Função para posicionar o navio no tabuleiro
void posicionaNavio(int tabuleiro[TAM][TAM], int linha, int coluna, char direcao) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        int l = linha, c = coluna;
        switch (direcao) {
            case 'H': c += i; break;
            case 'V': l += i; break;
            case 'D': l += i; c += i; break;
            case 'I': l += i; c -= i; break;
        }
        tabuleiro[l][c] = 3;  // valor 3 representa navio
    }
}

int main() {
    int tabuleiro[TAM][TAM] = {0};

    // Definição dos navios: linha, coluna, direção (H, V, D, I)
    struct {
        int linha;
        int coluna;
        char direcao;
    } navios[4] = {
        {1, 1, 'H'},  // navio horizontal - linha 1, coluna 1
        {4, 6, 'V'},  // navio vertical - linha 4, coluna 6
        {3, 3, 'D'},  // navio diagonal principal - linha 3, coluna 3 (deslocado para não colidir)
        {7, 9, 'I'}   // navio diagonal inversa - linha 7, coluna 9 (deslocado)
    };

    // Tenta posicionar cada navio
    for (int i = 0; i < 4; i++) {
        if (podePosicionar(tabuleiro, navios[i].linha, navios[i].coluna, navios[i].direcao)) {
            posicionaNavio(tabuleiro, navios[i].linha, navios[i].coluna, navios[i].direcao);
        } else {
            printf("Não foi possível posicionar navio %d na posicao (%d,%d) com direcao %c\n",
                i + 1, navios[i].linha + 1, navios[i].coluna + 1, navios[i].direcao);
        }
    }

    // Exibir cabeçalho com letras das colunas
    printf("    ");
    for (int j = 0; j < TAM; j++) {
        printf("%c ", 'A' + j);
    }
    printf("\n");

    // Exibir tabuleiro completo
    for (int i = 0; i < TAM; i++) {
        printf("%2d  ", i + 1);
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}
