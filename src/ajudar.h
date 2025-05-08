#ifndef AJUDAR_H
#define AJUDAR_H
#include "estrutura.h"

int vizinhoRiscado(Tabuleiro *tab, int linha, int coluna);
int letraIgual_mesmaLinhaColuna(Tabuleiro *tab, int linha, int coluna);
int casaBrancaIgual_mesmaLinhaColuna(Tabuleiro *tab, int linha, int coluna);
int isolaCasas(Tabuleiro *tab, int linha, int coluna);
int ajudar(Tabuleiro *tab);
void ajudarRepetidamente(Tabuleiro *tab);

#endif