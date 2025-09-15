#include <stdio.h>

#define TAM 10
#define TAM_CONE 5
#define TAM_CRUZ 5
#define TAM_OCTA 5

// Inicializa o tabuleiro com 0 (água)
void inicializarTabuleiro(int tabuleiro[TAM][TAM]) {
    int i, j;
    for (i = 0; i < TAM; i++)
        for (j = 0; j < TAM; j++)
            tabuleiro[i][j] = 0;
}

// Valida se a posição do navio é válida
int validarPosicao(int linha, int coluna, char orientacao, int tabuleiro[TAM][TAM]) {
    int i, tamanhoNavio = 3;

    if (orientacao == 'H') {
        if (coluna + tamanhoNavio > TAM) return 0;
        for (i = coluna; i < coluna + tamanhoNavio; i++)
            if (tabuleiro[linha][i] == 3) return 0;
    }
    else if (orientacao == 'V') {
        if (linha + tamanhoNavio > TAM) return 0;
        for (i = linha; i < linha + tamanhoNavio; i++)
            if (tabuleiro[i][coluna] == 3) return 0;
    }
    else if (orientacao == 'D') {
        if (linha + tamanhoNavio > TAM || coluna + tamanhoNavio > TAM) return 0;
        for (i = 0; i < tamanhoNavio; i++)
            if (tabuleiro[linha + i][coluna + i] == 3) return 0;
    }
    else if (orientacao == 'd') {
        if (linha + tamanhoNavio > TAM || coluna - tamanhoNavio + 1 < 0) return 0;
        for (i = 0; i < tamanhoNavio; i++)
            if (tabuleiro[linha + i][coluna - i] == 3) return 0;
    }
    else return 0;

    return 1;
}

// Posiciona o navio no tabuleiro
void posicionarNavio(int linha, int coluna, char orientacao, int tabuleiro[TAM][TAM]) {
    int i, tamanhoNavio = 3;

    if (orientacao == 'H')
        for (i = coluna; i < coluna + tamanhoNavio; i++)
            tabuleiro[linha][i] = 3;
    else if (orientacao == 'V')
        for (i = linha; i < linha + tamanhoNavio; i++)
            tabuleiro[i][coluna] = 3;
    else if (orientacao == 'D')
        for (i = 0; i < tamanhoNavio; i++)
            tabuleiro[linha + i][coluna + i] = 3;
    else if (orientacao == 'd')
        for (i = 0; i < tamanhoNavio; i++)
            tabuleiro[linha + i][coluna - i] = 3;
}

// Cria habilidade Cone (5x5)
void criarHabilidadeCone(int cone[TAM_CONE][TAM_CONE]) {
    int centro = TAM_CONE / 2;
    int i, j;
    for (i = 0; i < TAM_CONE; i++) {
        for (j = 0; j < TAM_CONE; j++) {
            if (j >= centro - i && j <= centro + i)
                cone[i][j] = 1;
            else
                cone[i][j] = 0;
        }
    }
}

// Cria habilidade Cruz (5x5)
void criarHabilidadeCruz(int cruz[TAM_CRUZ][TAM_CRUZ]) {
    int centro = TAM_CRUZ / 2;
    int i, j;
    for (i = 0; i < TAM_CRUZ; i++) {
        for (j = 0; j < TAM_CRUZ; j++) {
            if (i == centro || j == centro)
                cruz[i][j] = 1;
            else
                cruz[i][j] = 0;
        }
    }
}

// Cria habilidade Octaedro (5x5)
void criarHabilidadeOctaedro(int octa[TAM_OCTA][TAM_OCTA]) {
    int centro = TAM_OCTA / 2;
    int i, j;
    for (i = 0; i < TAM_OCTA; i++) {
        for (j = 0; j < TAM_OCTA; j++) {
            // Fórmula para losango: |i - centro| + |j - centro| <= centro
            int dist_i = (i > centro) ? i - centro : centro - i;
            int dist_j = (j > centro) ? j - centro : centro - j;
            if (dist_i + dist_j <= centro)
                octa[i][j] = 1;
            else
                octa[i][j] = 0;
        }
    }
}

// Sobrepõe habilidade no tabuleiro
void aplicarHabilidade(int tabuleiro[TAM][TAM], int habilidade[5][5], int tamHabilidade, int origemLinha, int origemColuna) {
    int centro = tamHabilidade / 2;
    int i, j;
    for (i = 0; i < tamHabilidade; i++) {
        for (j = 0; j < tamHabilidade; j++) {
            int linhaTab = origemLinha - centro + i;
            int colTab = origemColuna - centro + j;
            if (linhaTab >= 0 && linhaTab < TAM && colTab >= 0 && colTab < TAM) {
                if (habilidade[i][j] == 1 && tabuleiro[linhaTab][colTab] != 3)
                    tabuleiro[linhaTab][colTab] = 5; // área afetada
            }
        }
    }
}

// Exibe o tabuleiro
void exibirTabuleiro(int tabuleiro[TAM][TAM]) {
    int i, j;
    printf("\nTabuleiro (0=agua, 3=navio, 5=habilidade):\n\n");
    for (i = 0; i < TAM; i++) {
        for (j = 0; j < TAM; j++)
            printf("%d ", tabuleiro[i][j]);
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAM][TAM];
    int cone[TAM_CONE][TAM_CONE], cruz[TAM_CRUZ][TAM_CRUZ], octa[TAM_OCTA][TAM_OCTA];

    // Inicializa tabuleiro e habilidades
    inicializarTabuleiro(tabuleiro);
    criarHabilidadeCone(cone);
    criarHabilidadeCruz(cruz);
    criarHabilidadeOctaedro(octa);

    // Posiciona 4 navios
    if (validarPosicao(2,3,'H',tabuleiro)) posicionarNavio(2,3,'H',tabuleiro);
    if (validarPosicao(5,7,'V',tabuleiro)) posicionarNavio(5,7,'V',tabuleiro);
    if (validarPosicao(0,0,'D',tabuleiro)) posicionarNavio(0,0,'D',tabuleiro);
    if (validarPosicao(0,9,'d',tabuleiro)) posicionarNavio(0,9,'d',tabuleiro);

    // Aplica habilidades
    aplicarHabilidade(tabuleiro, cone, TAM_CONE, 1, 3);
    aplicarHabilidade(tabuleiro, cruz, TAM_CRUZ, 5, 5);
    aplicarHabilidade(tabuleiro, octa, TAM_OCTA, 7, 1);

    // Exibe o tabuleiro final
    exibirTabuleiro(tabuleiro);

    return 0;
}
