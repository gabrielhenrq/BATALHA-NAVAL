#include <stdio.h>

// Função para inicializar o tabuleiro com 0 (água)
int inicializarTabuleiro(int tabuleiro[10][10]) {
    int i, j;
    for (i = 0; i < 10; i++) {        // percorre as linhas
        for (j = 0; j < 10; j++) {    // percorre as colunas
            tabuleiro[i][j] = 0;      // define a posição como água
        }
    }
    return 0;
}

// Função para validar se é possível posicionar um navio
int validarPosicao(int linha, int coluna, char orientacao, int tabuleiro[10][10]) {
    int i;
    int tamanhoNavio = 3; // neste caso, todos os navios têm tamanho fixo 3

    // Verifica se a posição inicial está dentro dos limites do tabuleiro
    if (linha < 0 || linha >= 10 || coluna < 0 || coluna >= 10) {
        return 0; // posição inválida
    }

    // Caso a orientação seja horizontal
    if (orientacao == 'H') {
        // Verifica se o navio cabe até o final da linha
        if (coluna + tamanhoNavio > 10) return 0;
        // Verifica se já existe um navio nas posições desejadas
        for (i = coluna; i < coluna + tamanhoNavio; i++) {
            if (tabuleiro[linha][i] == 3) return 0;
        }
    } 
    // Caso a orientação seja vertical
    else if (orientacao == 'V') {
        // Verifica se o navio cabe até o final da coluna
        if (linha + tamanhoNavio > 10) return 0;
        // Verifica se já existe um navio nas posições desejadas
        for (i = linha; i < linha + tamanhoNavio; i++) {
            if (tabuleiro[i][coluna] == 3) return 0;
        }
    } 
    // Orientação inválida
    else {
        return 0;
    }

    return 1; // posição válida
}

// Função que realmente posiciona o navio no tabuleiro
int posicionarNavio(int linha, int coluna, char orientacao, int tabuleiro[10][10]) {
    int i;
    int tamanhoNavio = 3;

    if (orientacao == 'H') {
        for (i = coluna; i < coluna + tamanhoNavio; i++) {
            tabuleiro[linha][i] = 3; // marca a posição do navio
        }
    } else if (orientacao == 'V') {
        for (i = linha; i < linha + tamanhoNavio; i++) {
            tabuleiro[i][coluna] = 3;
        }
    }
    return 0;
}

// Função para exibir o tabuleiro na tela
int exibirTabuleiro(int tabuleiro[10][10]) {
    int i, j;
    printf("Tabuleiro Batalha Naval (0=agua, 3=navio):\n\n");
    for (i = 0; i < 10; i++) { // percorre linhas
        for (j = 0; j < 10; j++) { // percorre colunas
            printf("%d ", tabuleiro[i][j]); // imprime cada posição
        }
        printf("\n"); // quebra de linha a cada linha do tabuleiro
    }
    return 0;
}

int main() {
    int tabuleiro[10][10]; // matriz 10x10 representando o tabuleiro

    // Posições e orientações dos navios
    int linhaNavio1 = 2, colunaNavio1 = 3;
    char orientacaoNavio1 = 'H'; // horizontal

    int linhaNavio2 = 5, colunaNavio2 = 7;
    char orientacaoNavio2 = 'V'; // vertical

    // Inicializa o tabuleiro
    inicializarTabuleiro(tabuleiro);

    // Valida e posiciona o navio 1
    if (!validarPosicao(linhaNavio1, colunaNavio1, orientacaoNavio1, tabuleiro)) {
        printf("Posicao invalida para o navio 1.\n");
        return 1; // encerra o programa se não couber
    }
    posicionarNavio(linhaNavio1, colunaNavio1, orientacaoNavio1, tabuleiro);

    // Valida e posiciona o navio 2
    if (!validarPosicao(linhaNavio2, colunaNavio2, orientacaoNavio2, tabuleiro)) {
        printf("Posicao invalida para o navio 2.\n");
        return 1;
    }
    posicionarNavio(linhaNavio2, colunaNavio2, orientacaoNavio2, tabuleiro);

    // Exibe o tabuleiro final
    exibirTabuleiro(tabuleiro);

    return 0;
}
