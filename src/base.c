#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "estrutura.h"

// função para visualizar o jogo
void visualizarJogo(Tabuleiro *tab)
{
    for (int i = 0; i < tab->linhas; i++)
    {
        for (int j = 0; j < tab->colunas; j++)
            printf("%c ", tab->matriz[i][j]);

        printf("\n");
    }
}

// função para pintar a casa a branco
void pintarABranco(Tabuleiro *tab, int linha, char coluna)
{
    if (linha >= 0 && linha < tab->linhas && (coluna - 'a') >= 0 && (coluna - 'a') < tab->colunas)
    {
        if (tab->matriz[linha][coluna - 'a'] >= 'a' && tab->matriz[linha][coluna - 'a'] <= 'z')
            tab->matriz[linha][coluna - 'a'] = toupper(tab->matriz[linha][coluna - 'a']);
    }
}

// função para riscar a casa
void riscar(Tabuleiro *tab, int linha, char coluna)
{
    if (linha >= 0 && linha < tab->linhas && (coluna - 'a') >= 0 && (coluna - 'a') < tab->colunas)
        tab->matriz[linha][coluna - 'a'] = '#';
}