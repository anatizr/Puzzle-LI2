#ifndef JOGO_H
#define JOGO_H

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

// Protótipos das funções
void visualizarJogo(Tabuleiro *tab);
void pintarABranco(Tabuleiro *tab, int linha, char coluna);
void riscar(Tabuleiro *tab, int linha, char coluna);
void lerFicheiro(Tabuleiro *tab, char *nomeFicheiro);
void guardarFicheiro(Tabuleiro *tab, char *nomeFicheiro);
void desfazer(Tabuleiro *tab, Historico **hist);
void guardarHistorico(Historico **hist, Tabuleiro *tab);
int verificarRestricoes(Tabuleiro *tab);

#endif