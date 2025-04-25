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
    printf("Escolha um nível para jogar:\n1 - tabuleiro 5x5\n2 - tabuleiro 9x9\n3 - tabuleiro 20x20\n\n");
    int nivel;
    scanf("%d", &nivel);
    if (nivel == 1) lerFicheiro(&tab, "tabuleiros/tab1.txt");
    else if (nivel == 2) lerFicheiro(&tab, "tabuleiros/tab2.txt");
    else if (nivel == 3) lerFicheiro(&tab, "tabuleiros/tab3.txt");
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
            exit(0);
        }
        else if (cmd == '?')
        {
            printf("\n===COMANDOS DISPONÍVEIS===\nb : pintar a casa de branco;\nr : riscar a casa;\nl : ler tabuleiro de um ficheiro;\ng : guardar tabuleiro num ficheiro;\nd : desfazer o último comando executado;\nv : verifica e aponta as restrições violadas;\ns : sair do jogo.\n\n");
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
        else
            printf("Comando inválido.\n");
    }
    while (hist != NULL)
    {
        Historico *temp = hist;
        hist = hist->anterior;
        free(temp);
    }
    return 0;
}
