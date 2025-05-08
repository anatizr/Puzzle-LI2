#ifndef RESOLVER_H
#define RESOLVER_H
#include "estrutura.h"

int serValido(Tabuleiro *tab, int linha, int coluna, char temp);
int solve(Tabuleiro *tab, int linha, int coluna);
void tecnicas(Tabuleiro *tab);

#endif