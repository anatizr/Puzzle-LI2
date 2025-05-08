#include <stdio.h>
#include <stdlib.h>
#include "jogo.h"

int main()
{
    Tabuleiro tab;
    Historico *hist = NULL;

    int linha;
    char coluna, cmd;

    printf("\nBem vindo ao Jogo de Puzzle !\n\n");
    printf("Escolha um nível para jogar:\n1 - tabuleiro 5x5\n2 - tabuleiro 9x9\n3 - tabuleiro 20x20\n4 - tabuleiro 26x26\n\n");
    int nivel;
    scanf("%d", &nivel);
    if (nivel == 1)
        lerFicheiro(&tab, "tabuleiros/tab1.txt");
    else if (nivel == 2)
        lerFicheiro(&tab, "tabuleiros/tab2.txt");
    else if (nivel == 3)
        lerFicheiro(&tab, "tabuleiros/tab3.txt");
    else if (nivel == 4)
        lerFicheiro(&tab, "tabuleiros/tab4.txt");
    else
    {
        printf("Nível inválido. A sair do jogo ...\n");
        exit(0);
    }

    while (1)
    {
        visualizarJogo(&tab);

        printf("\nDigite um comando (? para ajuda) :\n\n");
        scanf(" %c", &cmd); // tem um espaço antes do %c
        if (cmd == 'b' || cmd == 'r')
        {
            scanf("%d %c", &linha, &coluna);
            guardarHistorico(&hist, &tab);
            if (cmd == 'b')
                pintarABranco(&tab, linha, coluna);
            else
                riscar(&tab, linha, coluna);
        }
        else if (cmd == 's')
        {
            printf("A sair do jogo ...\n");
            while (hist != NULL)
            {
                Historico *temp = hist;
                hist = hist->anterior;
                free(temp);
            }
            exit(0);
        }
        else if (cmd == '?')
        {
            printf("\n===COMANDOS DISPONÍVEIS===\n\n");
            printf("|----------------|--------------------------------------------------------|\n");
            printf("| Comando        | Descrição                                              |\n");
            printf("|----------------|--------------------------------------------------------|\n");
            printf("| g <ficheiro>   | Guarda o estado atual do jogo num ficheiro.            |\n");
            printf("| l <ficheiro>   | Carrega o estado do jogo a partir de um ficheiro.      |\n");
            printf("| <coordenada>   | Seleciona uma célula (ex: b3).                         |\n");
            printf("| b <coordenada> | Pinta a célula a branco (letra maiúscula).             |\n");
            printf("| r <coordenada> | Risca a célula (substitui por '#').                    |\n");
            printf("| v              | Verifica o estado atual e mostra violações das regras. |\n");
            printf("| a              | Aplica inferências automáticas com base nas regras.    |\n");
            printf("| A              | Repete o comando 'a' até não haver mais alterações.    |\n");
            printf("| R              | Resolve automaticamente o puzzle (se possível).        |\n");
            printf("| d              | Desfaz o último comando executado.                     |\n");
            printf("| s              | Sai do jogo.                                           |\n");
            printf("| ?              | Mostra esta ajuda.                                     |\n");
            printf("|----------------|--------------------------------------------------------|\n\n");
        }
        else if (cmd == 'l')
        {
            char nomeFicheiro[50];
            scanf("%s", nomeFicheiro);
            lerFicheiro(&tab, nomeFicheiro);
        }
        else if (cmd == 'g')
        {
            char nomeFicheiro[50];
            scanf("%s", nomeFicheiro);
            guardarFicheiro(&tab, nomeFicheiro);
        }
        else if (cmd == 'd')
        {
            if (hist != NULL)
                desfazer(&tab, &hist);
            else
                printf("Não há comandos para desfazer.\n");
        }
        else if (cmd == 'v')
            verificarRestricoes(&tab);
        else if (cmd == 'a')
        {
            if (ajudar(&tab))
                printf("Inferências aplicadas com sucesso!\n");
            else
                printf("Nenhuma inferência possível foi encontrada.\n");
        }
        else if (cmd == 'A')
        {
            ajudarRepetidamente(&tab);
            printf("Todas as inferências possíveis foram aplicadas!\n");
        }
        else if (cmd == 'R')
        {
            tecnicas(&tab);
            ajudarRepetidamente(&tab);
            if (solve(&tab, 0, 0))
                printf("Puzzle resolvido com sucesso!\n");
            else
                printf("Não foi possível resolver o puzzle.\n");
        }
        else
            printf("Comando inválido.\n");
    }
    return 0;
}
