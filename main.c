#include <stdio.h>

int inicializarTabuleiro(int tabuleiro[10][10]) {
    int i, j;
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            tabuleiro[i][j] = 0;
        }
    }
    return 0;
}

int validarPosicao(int linha, int coluna, char orientacao, int tabuleiro[10][10]) {
    int i;
    int tamanhoNavio = 3;

    if (linha < 0 || linha >= 10 || coluna < 0 || coluna >= 10) {
        return 0;
    }

    if (orientacao == 'H') {
        if (coluna + tamanhoNavio > 10) return 0;
        for (i = coluna; i < coluna + tamanhoNavio; i++) {
            if (tabuleiro[linha][i] == 3) return 0;
        }
    } else if (orientacao == 'V') {
        if (linha + tamanhoNavio > 10) return 0;
        for (i = linha; i < linha + tamanhoNavio; i++) {
            if (tabuleiro[i][coluna] == 3) return 0;
        }
    } else {
        return 0;
    }

    return 1;
}

int posicionarNavio(int linha, int coluna, char orientacao, int tabuleiro[10][10]) {
    int i;
    int tamanhoNavio = 3;

    if (orientacao == 'H') {
        for (i = coluna; i < coluna + tamanhoNavio; i++) {
            tabuleiro[linha][i] = 3;
        }
    } else if (orientacao == 'V') {
        for (i = linha; i < linha + tamanhoNavio; i++) {
            tabuleiro[i][coluna] = 3;
        }
    }
    return 0;
}

int exibirTabuleiro(int tabuleiro[10][10]) {
    int i, j;
    printf("Tabuleiro Batalha Naval (0=agua, 3=navio):\n\n");
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
    return 0;
}

int main() {
    int tabuleiro[10][10];
    int linhaNavio1 = 2, colunaNavio1 = 3;
    char orientacaoNavio1 = 'H';

    int linhaNavio2 = 5, colunaNavio2 = 7;
    char orientacaoNavio2 = 'V';

    inicializarTabuleiro(tabuleiro);

    if (!validarPosicao(linhaNavio1, colunaNavio1, orientacaoNavio1, tabuleiro)) {
        printf("Posicao invalida para o navio 1.\n");
        return 1;
    }
    posicionarNavio(linhaNavio1, colunaNavio1, orientacaoNavio1, tabuleiro);

    if (!validarPosicao(linhaNavio2, colunaNavio2, orientacaoNavio2, tabuleiro)) {
        printf("Posicao invalida para o navio 2.\n");
        return 1;
    }
    posicionarNavio(linhaNavio2, colunaNavio2, orientacaoNavio2, tabuleiro);

    exibirTabuleiro(tabuleiro);

    return 0;
}
