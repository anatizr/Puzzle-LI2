#ifndef DESFAZER_H
#define DESFAZER_H
#include "estrutura.h"

void desfazer(Tabuleiro *tab, Historico **hist);
void guardarHistorico(Historico **hist, Tabuleiro *tab);

#endif