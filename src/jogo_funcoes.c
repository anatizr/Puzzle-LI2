#include <stdio.h>
#include <stdlib.h> // para malloc e free

typedef struct tabuleiro
{
    char matriz[20][20];
    int linhas, colunas;
} Tabuleiro;

typedef struct historico
{
    Tabuleiro tabAnterior;
    struct historico *anterior;
} Historico;

// função para visualizar o jogo
void visualizarJogo(Tabuleiro *tab)
{
    for (int i = 0; i < tab->linhas; i++)
    {
        for (int j = 0; j < tab->colunas; j++)
            printf("%c", tab->matriz[i][j]);

        printf("\n");
    }
}

// função para pintar a casa a branco
void pintarABranco(Tabuleiro *tab, int linha, char coluna)
{
    if (linha >= 0 && linha < tab->linhas && (coluna - 'a') >= 0 && (coluna - 'a') < tab->colunas)
    {
        if (tab->matriz[linha][coluna - 'a'] >= 'a' && tab->matriz[linha][coluna - 'a'] <= 'z')
            tab->matriz[linha][coluna - 'a'] = tab->matriz[linha][coluna - 'a'] - ('a' - 'A');
    }
}

// função para riscar a casa
void riscar(Tabuleiro *tab, int linha, char coluna)
{
    if (linha >= 0 && linha < tab->linhas && (coluna - 'a') >= 0 && (coluna - 'a') < tab->colunas)
        tab->matriz[linha][coluna - 'a'] = '#';
}

// função para ler o tabuleiro de um ficheiro
void lerFicheiro(Tabuleiro *tab, char *nomeFicheiro)
{
    FILE *ficheiro = fopen(nomeFicheiro, "r");
    if (ficheiro == NULL)
    {
        printf("Erro ao abrir o ficheiro %s\n", nomeFicheiro);
        return;
    }
    fscanf(ficheiro, "%d %d", &tab->linhas, &tab->colunas);

    for (int i = 0; i < tab->linhas; i++)
        for (int j = 0; j < tab->colunas; j++)
            fscanf(ficheiro, " %c", &tab->matriz[i][j]);

    fclose(ficheiro);
    printf("Tabuleiro lido com sucesso, ficheiro %s\n\n", nomeFicheiro);
}

// função para guardar o tabuleiro num ficheiro
void guardarFicheiro(Tabuleiro *tab, char *nomeFicheiro)
{
    FILE *ficheiro = fopen(nomeFicheiro, "w");
    if (ficheiro == NULL)
    {
        printf("Erro ao abrir o ficheiro %s\n", nomeFicheiro);
        return;
    }

    fprintf(ficheiro, "%d %d\n", tab->linhas, tab->colunas);
    for (int i = 0; i < tab->linhas; i++)
    {
        for (int j = 0; j < tab->colunas; j++)
            fprintf(ficheiro, " %c", tab->matriz[i][j]);
        fprintf(ficheiro, "\n");
    }

    fclose(ficheiro);
    printf("Tabuleiro guardado com sucesso no ficheiro %s\n\n", nomeFicheiro);
}

// função para desfazer o último comando executado
void desfazer(Tabuleiro *tab, Historico **historico)
{
    if (*historico != NULL)
    {
        *tab = (*historico)->tabAnterior;
        Historico *temp = *historico;
        *historico = (*historico)->anterior;
        free(temp);
    }
}

// função para guardar o histórico
void guardarHistorico(Historico **historico, Tabuleiro *tab)
{
    Historico *novo = (Historico *)malloc(sizeof(Historico));
    novo->tabAnterior = *tab;
    novo->anterior = *historico;
    *historico = novo;
}

// função para verificar as restrições das casas brancas e riscadas
void verificarRestricoes(Tabuleiro *tab)
{
    for (int i = 0; i < tab->linhas; i++)
    {
        for (int j = 0; j < tab->colunas; j++)
        {
            char casa = tab->matriz[i][j];
            if (casa == '#')
            {
                // verificar se todas as casas vizinhas (ortogonais) estão pintadas a branco
                if ((i > 0 && tab->matriz[i - 1][j] >= 'a' && tab->matriz[i - 1][j] <= 'z') ||
                    (i < tab->linhas - 1 && tab->matriz[i + 1][j] >= 'a' && tab->matriz[i + 1][j] <= 'z') ||
                    (j > 0 && tab->matriz[i][j - 1] >= 'a' && tab->matriz[i][j - 1] <= 'z') ||
                    (j < tab->colunas - 1 && tab->matriz[i][j + 1] >= 'a' && tab->matriz[i][j + 1] <= 'z'))
                {
                    printf("Restrição violada: Casa riscada (%d, %d) tem vizinhos não pintados a branco.\n", i, j);
                }
            }
            else if (casa >= 'A' && casa <= 'Z')
            {
                // Verificar se há réplicas na mesma linha ou coluna
                for (int k = 0; k < tab->linhas; k++)
                {
                    if (k != i && tab->matriz[k][j] == casa)
                    {
                        printf("Restrição violada: Casa branca (%d, %d) tem réplica na linha %d.\n", i, j, k);
                    }
                }
                for (int k = 0; k < tab->colunas; k++)
                {
                    if (k != j && tab->matriz[i][k] == casa)
                    {
                        printf("Restrição violada: Casa branca (%d, %d) tem réplica na coluna %d.\n", i, j, k);
                    }
                }
            }
        }
    }
}
