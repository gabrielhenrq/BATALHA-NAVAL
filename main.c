#include <stdio.h>

// Função para inicializar o tabuleiro com 0 (água)
void inicializarTabuleiro(int tabuleiro[10][10]) {
    int i, j;
    for (i = 0; i < 10; i++) {        // percorre as linhas
        for (j = 0; j < 10; j++) {    // percorre as colunas
            tabuleiro[i][j] = 0;      // define a posição como água
        }
    }
}

// Função para validar se é possível posicionar um navio
int validarPosicao(int linha, int coluna, char orientacao, int tabuleiro[10][10]) {
    int i;
    int tamanhoNavio = 3;

    // Orientação Horizontal
    if (orientacao == 'H') {
        if (coluna + tamanhoNavio > 10) return 0;
        for (i = coluna; i < coluna + tamanhoNavio; i++) {
            if (tabuleiro[linha][i] == 3) return 0;
        }
    }
    // Orientação Vertical
    else if (orientacao == 'V') {
        if (linha + tamanhoNavio > 10) return 0;
        for (i = linha; i < linha + tamanhoNavio; i++) {
            if (tabuleiro[i][coluna] == 3) return 0;
        }
    }
    // Orientação Diagonal Principal (\)
    else if (orientacao == 'D') {
        if (linha + tamanhoNavio > 10 || coluna + tamanhoNavio > 10) return 0;
        for (i = 0; i < tamanhoNavio; i++) {
            if (tabuleiro[linha + i][coluna + i] == 3) return 0;
        }
    }
    // Orientação Diagonal Secundária (/)
    else if (orientacao == 'd') {
        if (linha + tamanhoNavio > 10 || coluna - tamanhoNavio + 1 < 0) return 0;
        for (i = 0; i < tamanhoNavio; i++) {
            if (tabuleiro[linha + i][coluna - i] == 3) return 0;
        }
    }
    else {
        return 0; // Orientação inválida
    }

    return 1; // posição válida
}

// Função que posiciona o navio
void posicionarNavio(int linha, int coluna, char orientacao, int tabuleiro[10][10]) {
    int i;
    int tamanhoNavio = 3;

    if (orientacao == 'H') {
        for (i = coluna; i < coluna + tamanhoNavio; i++) {
            tabuleiro[linha][i] = 3;
        }
    } 
    else if (orientacao == 'V') {
        for (i = linha; i < linha + tamanhoNavio; i++) {
            tabuleiro[i][coluna] = 3;
        }
    } 
    else if (orientacao == 'D') {
        for (i = 0; i < tamanhoNavio; i++) {
            tabuleiro[linha + i][coluna + i] = 3;
        }
    }
    else if (orientacao == 'd') {
        for (i = 0; i < tamanhoNavio; i++) {
            tabuleiro[linha + i][coluna - i] = 3;
        }
    }
}

// Função para exibir o tabuleiro na tela
void exibirTabuleiro(int tabuleiro[10][10]) {
    int i, j;
    printf("\nTabuleiro Batalha Naval (0=agua, 3=navio):\n\n");
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[10][10];

    // Inicializa o tabuleiro
    inicializarTabuleiro(tabuleiro);

    // Definição das posições dos 4 navios
    int linha1 = 2, coluna1 = 3; char o1 = 'H'; // Horizontal
    int linha2 = 5, coluna2 = 7; char o2 = 'V'; // Vertical
    int linha3 = 0, coluna3 = 0; char o3 = 'D'; // Diagonal principal
    int linha4 = 0, coluna4 = 9; char o4 = 'd'; // Diagonal secundária

    // Posiciona os navios com validação
    if (validarPosicao(linha1, coluna1, o1, tabuleiro)) posicionarNavio(linha1, coluna1, o1, tabuleiro);
    else printf("Posicao invalida para navio 1.\n");

    if (validarPosicao(linha2, coluna2, o2, tabuleiro)) posicionarNavio(linha2, coluna2, o2, tabuleiro);
    else printf("Posicao invalida para navio 2.\n");

    if (validarPosicao(linha3, coluna3, o3, tabuleiro)) posicionarNavio(linha3, coluna3, o3, tabuleiro);
    else printf("Posicao invalida para navio 3.\n");

    if (validarPosicao(linha4, coluna4, o4, tabuleiro)) posicionarNavio(linha4, coluna4, o4, tabuleiro);
    else printf("Posicao invalida para navio 4.\n");

    // Exibe tabuleiro
    exibirTabuleiro(tabuleiro);

    return 0;
}
