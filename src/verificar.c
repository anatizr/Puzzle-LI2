#include <stdio.h>
#include "estrutura.h"
#include "caminho.h"

// função para verificar as restrições
int verificarRestricoes(Tabuleiro *tab)
{
    int violacoes = 0;

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
                    printf("Restrição violada: Casa riscada (%d, %c) tem vizinhos não pintados a branco.\n", i, 'a' + j);
                    violacoes = 1;
                }
            }
            else if (casa >= 'A' && casa <= 'Z')
            {
                // Verificar se há réplicas na mesma linha ou coluna
                for (int k = 0; k < tab->linhas; k++)
                {
                    if (k != i && tab->matriz[k][j] == casa)
                    {
                        printf("Restrição violada: Casa branca (%d, %c) tem réplica na linha %d.\n", i, 'a' + j, k);
                        violacoes = 1;
                    }
                }
                for (int k = 0; k < tab->colunas; k++)
                {
                    if (k != j && tab->matriz[i][k] == casa)
                    {
                        printf("Restrição violada: Casa branca (%d, %c) tem réplica na coluna %c.\n", i, 'a' + j, 'a' + k);
                        violacoes = 1;
                    }
                }
            }
        }
    }
    if (verificarCaminho(tab))
        violacoes = 1;

    return violacoes;
}