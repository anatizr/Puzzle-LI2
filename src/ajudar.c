#include <ctype.h>
#include "estrutura.h"
#include "base.h"
#include "caminho.h"

// função auxiliar que verifica se uma casa tem algum vizinho riscado
int vizinhoRiscado(Tabuleiro *tab, int linha, int coluna)
{
    if (linha > 0 && tab->matriz[linha - 1][coluna] == '#')
        return 1;
    if (linha < tab->linhas - 1 && tab->matriz[linha + 1][coluna] == '#')
        return 1;
    if (coluna > 0 && tab->matriz[linha][coluna - 1] == '#')
        return 1;
    if (coluna < tab->colunas - 1 && tab->matriz[linha][coluna + 1] == '#')
        return 1;

    return 0;
}

// função auxiliar que verifica se há alguma casa (minuscula ou maiuscula) com a mesma letra na linha ou coluna
int letraIgual_mesmaLinhaColuna(Tabuleiro *tab, int linha, int coluna)
{
    char letra = tab->matriz[linha][coluna];

    for (int j = 0; j < tab->colunas; j++)
    {
        if (j != coluna &&
            ((tab->matriz[linha][j] == letra) || (tab->matriz[linha][j] == toupper(letra))))
            return 1;
    }

    for (int i = 0; i < tab->linhas; i++)
    {
        if (i != linha &&
            ((tab->matriz[i][coluna] == letra) || (tab->matriz[i][coluna] == toupper(letra))))
            return 1;
    }
    return 0;
}

// função auxiliar que verifica se há alguma casa (branca/maiuscula) com a mesma letra na linha ou coluna
int casaBrancaIgual_mesmaLinhaColuna(Tabuleiro *tab, int linha, int coluna)
{
    char casa = tab->matriz[linha][coluna];

    for (int j = 0; j < tab->colunas; j++)
    {
        if (j != coluna &&
            (tab->matriz[linha][j] == toupper(casa)))
            return 1;
    }

    for (int i = 0; i < tab->linhas; i++)
    {
        if (i != linha &&
            (tab->matriz[i][coluna] == toupper(casa)))
            return 1;
    }
    return 0;
}

// função auxiliar que verifica se riscar a casa isolaria outras casas brancas
int isolaCasas(Tabuleiro *tab, int linha, int coluna)
{
    Tabuleiro temp = *tab;
    temp.matriz[linha][coluna] = '#';

    int visitadas[26][26] = {0};
    int i_inicio = -1, j_inicio = -1;

    for (int i = 0; i < temp.linhas && i_inicio == -1; i++)
    {
        for (int j = 0; j < temp.colunas && j_inicio == -1; j++)
        {
            if (temp.matriz[i][j] != '#')
            {
                i_inicio = i;
                j_inicio = j;
            }
        }
    }
    if (i_inicio == -1)
        return 0;

    dfs(&temp, i_inicio, j_inicio, visitadas);

    for (int i = 0; i < temp.linhas; i++)
    {
        for (int j = 0; j < temp.colunas; j++)
        {
            if (temp.matriz[i][j] != '#' && !visitadas[i][j])
                return 1;
        }
    }
    return 0;
}

// função para implemantar o comando 'a'
int ajudar(Tabuleiro *tab)
{
    int alteracoes = 0;

    for (int i = 0; i < tab->linhas; i++)
    {
        for (int j = 0; j < tab->colunas; j++)
        {
            char c = tab->matriz[i][j];
            int casa_ignorada = (c == '#' || (c >= 'A' && c <= 'Z'));

            if (!casa_ignorada)
            {
                if (!letraIgual_mesmaLinhaColuna(tab, i, j))
                {
                    pintarABranco(tab, i, j + 'a');
                    alteracoes = 1;
                }

                if (vizinhoRiscado(tab, i, j) && !casaBrancaIgual_mesmaLinhaColuna(tab, i, j))
                {
                    pintarABranco(tab, i, j + 'a');
                    alteracoes = 1;
                }

                if (isolaCasas(tab, i, j) && !casaBrancaIgual_mesmaLinhaColuna(tab, i, j))
                {
                    pintarABranco(tab, i, j + 'a');
                    alteracoes = 1;
                }
                if (casaBrancaIgual_mesmaLinhaColuna(tab, i, j) && (!vizinhoRiscado(tab, i, j) || !isolaCasas(tab, i, j)))
                {
                    riscar(tab, i, j + 'a');
                    alteracoes = 1;
                }
            }
        }
    }
    return alteracoes;
}

// função para implementar o comando 'A'
void ajudarRepetidamente(Tabuleiro *tab)
{
    int alteracoes;
    do
    {
        alteracoes = ajudar(tab);
    } while (alteracoes); 
}
