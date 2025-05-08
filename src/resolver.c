#include <ctype.h>
#include "estrutura.h"
#include "ajudar.h"
#include "caminho.h"

int serValido(Tabuleiro *tab, int linha, int coluna, char temp)
{
    int valido = 1;
    char original = tab->matriz[linha][coluna];
    tab->matriz[linha][coluna] = temp;

    if (temp == '#')
    {
        if (vizinhoRiscado(tab, linha, coluna) && !verificarCaminhoSilencioso(tab))
            valido = 0;
    }
    else if (temp >= 'A' && temp <= 'Z')
    {
        if (casaBrancaIgual_mesmaLinhaColuna(tab, linha, coluna))
            valido = 0;
    }
    if (valido && verificarCaminhoSilencioso(tab))
        valido = 0;

    tab->matriz[linha][coluna] = original;
    return valido;
}

int solve(Tabuleiro *tab, int linha, int coluna)
{
    if (linha == tab->linhas)
        return 1;

    else if (coluna == tab->colunas)
        return solve(tab, linha + 1, 0);

    else if (!(tab->matriz[linha][coluna] >= 'a' && tab->matriz[linha][coluna] <= 'z'))
        return solve(tab, linha, coluna + 1);

    else
    {
        if (serValido(tab, linha, coluna, toupper(tab->matriz[linha][coluna])))
        {
            char original = tab->matriz[linha][coluna];
            tab->matriz[linha][coluna] = toupper(tab->matriz[linha][coluna]);

            if (solve(tab, linha, coluna + 1))
                return 1;

            tab->matriz[linha][coluna] = original;
        }
        if (serValido(tab, linha, coluna, '#'))
        {
            char original = tab->matriz[linha][coluna];
            tab->matriz[linha][coluna] = '#';

            if (solve(tab, linha, coluna + 1))
                return 1;

            tab->matriz[linha][coluna] = original;
        }
    }
    return 0;
}

int iguais_adjacentes_horizontais(Tabuleiro *tab, int linha, int coluna)
{
    return (tab->matriz[linha][coluna - 1] == tab->matriz[linha][coluna + 1]);
}

int iguais_adjacentes_verticais(Tabuleiro *tab, int linha, int coluna)
{
    return (tab->matriz[linha - 1][coluna] == tab->matriz[linha + 1][coluna]);
}

void tecnicas(Tabuleiro *tab)
{
    for (int i = 0; i < tab->linhas; i++)
    {
        for (int j = 0; j < tab->colunas; j++)
        {
            char c = tab->matriz[i][j];

            if (j > 0 && j < tab->colunas - 1 &&
                c == tab->matriz[i][j - 1] &&
                c == tab->matriz[i][j + 1])
            {
                tab->matriz[i][j - 1] = '#';
                tab->matriz[i][j + 1] = '#';
                tab->matriz[i][j] = toupper(c);
            }

            if (i > 0 && i < tab->linhas - 1 &&
                c == tab->matriz[i - 1][j] &&
                c == tab->matriz[i + 1][j])
            {
                tab->matriz[i - 1][j] = '#';
                tab->matriz[i + 1][j] = '#';
                tab->matriz[i][j] = toupper(c);
            }

            if (j > 0 && j < tab->colunas - 1 &&
                iguais_adjacentes_horizontais(tab, i, j))
            {
                tab->matriz[i][j] = toupper(tab->matriz[i][j]);
            }

            if (i > 0 && i < tab->linhas - 1 &&
                iguais_adjacentes_verticais(tab, i, j))
            {
                tab->matriz[i][j] = toupper(tab->matriz[i][j]);
            }
        }
    }
}