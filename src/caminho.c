#include <stdio.h>
#include "estrutura.h"

// função para realizar busca em profundidade (DFS)
void dfs(Tabuleiro *tab, int linha, int coluna, int visitadas[26][26])
{
    if (linha < 0 || linha >= tab->linhas || coluna < 0 || coluna >= tab->colunas)
        return;

    if (visitadas[linha][coluna] || tab->matriz[linha][coluna] == '#')
        return;

    visitadas[linha][coluna] = 1;

    dfs(tab, linha - 1, coluna, visitadas);
    dfs(tab, linha + 1, coluna, visitadas);
    dfs(tab, linha, coluna - 1, visitadas);
    dfs(tab, linha, coluna + 1, visitadas);
}

// função para verificar se existe um caminho ortogonal entre as casas brancas (ou potencialmente brancas)
int verificarCaminho(Tabuleiro *tab)
{
    int visitadas[26][26] = {0};
    int i_inicio = -1, j_inicio = -1;

    for (int i = 0; i < tab->linhas && i_inicio == -1; i++)
    {
        for (int j = 0; j < tab->colunas && j_inicio == -1; j++)
        {
            if (tab->matriz[i][j] != '#')
            {
                i_inicio = i;
                j_inicio = j;
            }
        }
    }
    if (i_inicio == -1)
        return 1;

    dfs(tab, i_inicio, j_inicio, visitadas);

    for (int i = 0; i < tab->linhas; i++)
    {
        for (int j = 0; j < tab->colunas; j++)
        {
            if (tab->matriz[i][j] != '#' && !visitadas[i][j])
            {
                printf("Restrição violada: Não há caminho ortogonal entre a casa (%d, %c) e a casa (%d, %c)\n", i_inicio, 'a' + j_inicio, i, 'a' + j);
                return 1;
            }
        }
    }
    return 0;
}

// função auxiliar, verificarCaminho sem printf
int verificarCaminhoSilencioso(Tabuleiro *tab)
{
    int visitadas[26][26] = {0};
    int i_inicio = -1, j_inicio = -1;

    for (int i = 0; i < tab->linhas && i_inicio == -1; i++)
    {
        for (int j = 0; j < tab->colunas && j_inicio == -1; j++)
        {
            if (tab->matriz[i][j] != '#')
            {
                i_inicio = i;
                j_inicio = j;
            }
        }
    }
    if (i_inicio == -1)
        return 1;

    dfs(tab, i_inicio, j_inicio, visitadas);

    for (int i = 0; i < tab->linhas; i++)
    {
        for (int j = 0; j < tab->colunas; j++)
        {
            if (tab->matriz[i][j] != '#' && !visitadas[i][j])
                return 1;
        }
    }
    return 0;
}