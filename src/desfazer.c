#include <stdio.h>
#include <stdlib.h>
#include "estrutura.h"

// função para desfazer o último comando executado
void desfazer(Tabuleiro *tab, Historico **historico)
{
    if (*historico != NULL)
    {
        *tab = (*historico)->tabAnterior;
        Historico *temp = *historico;
        *historico = (*historico)->anterior;
        free(temp);
    }
}

// função para guardar o histórico
void guardarHistorico(Historico **historico, Tabuleiro *tab)
{
    Historico *novo = (Historico *)malloc(sizeof(Historico));
    novo->tabAnterior = *tab;
    novo->anterior = *historico;
    *historico = novo;
}
