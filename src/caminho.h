#ifndef CAMINHO_H
#define CAMINHO_H
#include "estrutura.h"

void dfs(Tabuleiro *tab, int linha, int coluna, int visitadas[26][26]);
int verificarCaminho(Tabuleiro *tab);
int verificarCaminhoSilencioso(Tabuleiro *tab);

#endif