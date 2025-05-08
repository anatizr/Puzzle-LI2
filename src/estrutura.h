#ifndef ESTRUTURA_H
#define ESTRUTURA_H

typedef struct tabuleiro
{
    char matriz[26][26];
    int linhas, colunas;
} Tabuleiro;

typedef struct historico
{
    Tabuleiro tabAnterior;
    struct historico *anterior;
} Historico;

#endif