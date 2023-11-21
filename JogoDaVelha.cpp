#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para armazenar dados do jogador
struct Jogador {
    char nome[50];
    int pontuacao;
};

// Prot�tipos de fun��es
void mostrarMenu();
void jogarJogo(int tamanhoTabuleiro);
void exibirTabuleiro(char **tabuleiro, int tamanho);
int realizarJogada(char **tabuleiro, int linha, int coluna, char jogador, int tamanho);
int verificarVitoria(char **tabuleiro, char jogador, int tamanho);
int verificarEmpate(char **tabuleiro, int tamanho);
void jogadaComputador(char **tabuleiro, char jogador, int tamanho);
void mostrarRanking(struct Jogador *jogadores, int numJogadores);
void salvarRanking(struct Jogador *jogadores, int numJogadores);

int main() {
    int opcao;
    do {
        mostrarMenu();
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                jogarJogo(3);  // Pode ser alterado para 5 para um tabuleiro 5x5
                break;
            case 2:
                printf("Ranking:\n");
                // Carregar dados do arquivo ou inicializar uma estrutura de jogadores
                struct Jogador jogadores[10];  // Supondo um m�ximo de 10 jogadores
                mostrarRanking(jogadores, 10);
                break;
            case 3:
                printf("Cr�ditos: Desenvolvido por [seu nome]\n");
                break;
            case 4:
                printf("Saindo do jogo. At� logo!\n");
                break;
            default:
                printf("Op��o inv�lida. Tente novamente.\n");
        }
    } while (opcao != 4);

    return 0;
}

void mostrarMenu() {
    printf("\n=== Menu ===\n");
    printf("1. Jogar\n");
    printf("2. Ver Ranking\n");
    printf("3. Cr�ditos\n");
    printf("4. Sair\n");
    printf("Escolha a op��o: ");
}

void jogarJogo(int tamanhoTabuleiro) {
    char **tabuleiro;
    char jogadorAtual = 'X';
    int linha, coluna, jogadaValida;

    // Aloca��o din�mica do tabuleiro
    tabuleiro = (char **)malloc(tamanhoTabuleiro * sizeof(char *));
    for (int i = 0; i < tamanhoTabuleiro; i++) {
        tabuleiro[i] = (char *)malloc(tamanhoTabuleiro * sizeof(char));
        memset(tabuleiro[i], ' ', tamanhoTabuleiro);
    }

    do {
        exibirTabuleiro(tabuleiro, tamanhoTabuleiro);

        if (jogadorAtual == 'X') {
            printf("Jogador X, insira a linha (0-%d) e coluna (0-%d) separadas por espa�o: ", tamanhoTabuleiro - 1,
                   tamanhoTabuleiro - 1);
            scanf("%d %d", &linha, &coluna);
            jogadaValida = realizarJogada(tabuleiro, linha, coluna, jogadorAtual, tamanhoTabuleiro);
        } else {
            printf("Computador (Jogador O) est� pensando...\n");
            jogadaComputador(tabuleiro, jogadorAtual, tamanhoTabuleiro);
            jogadaValida = 1;  // A jogada do computador � sempre v�lida
        }

        if (jogadaValida) {
            if (verificarVitoria(tabuleiro, jogadorAtual, tamanhoTabuleiro)) {
                exibirTabuleiro(tabuleiro, tamanhoTabuleiro);
                if (jogadorAtual == 'X') {
                    printf("Jogador X venceu!\n");
                } else {
                    printf("Computador (Jogador O) venceu!\n");
                }
                break;
            }

            if (verificarEmpate(tabuleiro, tamanhoTabuleiro)) {
                exibirTabuleiro(tabuleiro, tamanhoTabuleiro);
                printf("O jogo terminou em empate!\n");
                break;
            }

            jogadorAtual = (jogadorAtual == 'X') ? 'O' : 'X';
        } else {
            printf("Jogada inv�lida. Tente novamente.\n");
        }

    } while (1);

    // Libera��o de mem�ria
    for (int i = 0; i < tamanhoTabuleiro; i++) {
        free(tabuleiro[i]);
    }
    free(tabuleiro);
}

void exibirTabuleiro(char **tabuleiro, int tamanho) {
    printf("\n");
    for (int i = 0; i < tamanho; ++i) {
        for (int j = 0; j < tamanho; ++j) {
            printf("%c ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int realizarJogada(char **tabuleiro, int linha, int coluna, char jogador, int tamanho) {
    if (linha >= 0 && linha < tamanho && coluna >= 0 && coluna < tamanho && tabuleiro[linha][coluna] == ' ') {
        tabuleiro[linha][coluna] = jogador;
        return 1;
    } else {
        return 0;
    }
}

int verificarVitoria(char **tabuleiro, char jogador, int tamanho) {
    for (int i = 0; i < tamanho; ++i) {
        // Verifica linhas e colunas
        if ((tabuleiro[i][0] == jogador && tabuleiro[i][1] == jogador && tabuleiro[i][2] == jogador) ||
            (tabuleiro[0][i] == jogador && tabuleiro[1][i] == jogador && tabuleiro[2][i] == jogador)) {
            return 1;
        }
    }

    // Verifica diagonais
    if ((tabuleiro[0][0] == jogador && tabuleiro[1][1] == jogador && tabuleiro[2][2] == jogador) ||
        (tabuleiro[0][2] == jogador && tabuleiro[1][1] == jogador && tabuleiro[2][0] == jogador)) {
        return 1;
    }

    return 0;
}

int verificarEmpate(char **tabuleiro, int tamanho) {
    for (int i = 0; i < tamanho; ++i) {
        for (int j = 0; j < tamanho; ++j) {
            if (tabuleiro[i][j] == ' ') {
                return 0;
            }
        }
    }
    return 1;
}

void jogadaComputador(char **tabuleiro, char jogador, int tamanho) {
    // Estrat�gia simples: joga na primeira posi��o vazia encontrada
    for (int i = 0; i < tamanho; ++i) {
        for (int j = 0; j < tamanho; ++j) {
            if (tabuleiro[i][j] == ' ') {
                tabuleiro[i][j] = jogador;
                return;
            }
        }
    }
}

void mostrarRanking(struct Jogador *jogadores, int numJogadores) {
    // Carrega dados do arquivo ou inicializa jogadores com pontua��es fict�cias
    for (int i = 0; i < numJogadores; ++i) {
        strcpy(jogadores[i].nome, "Jogador");
        jogadores[i].pontuacao = rand() % 100;  // Pontua��o fict�cia
    }

    // Classifica os jogadores pelo ranking (pontua��o)
    for (int i = 0; i < numJogadores - 1; ++i) {
        for (int j = i + 1; j < numJogadores; ++j) {
            if (jogadores[i].pontuacao < jogadores[j].pontuacao) {
                // Troca de posi��es
                struct Jogador temp = jogadores[i];
                jogadores[i] = jogadores[j];
                jogadores[j] = temp;
            }
        }
    }

    // Exibe o ranking
    for (int i = 0; i < numJogadores; ++i) {
        printf("%d. %s - Pontua��o: %d\n", i + 1, jogadores[i].nome, jogadores[i].pontuacao);
    }

    // Salva o ranking no arquivo
    salvarRanking(jogadores, numJogadores);
}

void salvarRanking(struct Jogador *jogadores, int numJogadores) {
    FILE *arquivo = fopen("ranking.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de ranking.\n");
        return;
    }

    for (int i = 0; i < numJogadores; ++i) {
        fprintf(arquivo, "%s %d\n", jogadores[i].nome, jogadores[i].pontuacao);
    }

    fclose(arquivo);
}
