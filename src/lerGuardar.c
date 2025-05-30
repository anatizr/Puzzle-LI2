#include <stdio.h>
#include "estrutura.h"

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
    // printf("Tabuleiro lido com sucesso, ficheiro %s\n\n", nomeFicheiro);
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
