#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

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

// função para visualizar o jogo
void visualizarJogo(Tabuleiro *tab)
{
    for (int i = 0; i < tab->linhas; i++)
    {
        for (int j = 0; j < tab->colunas; j++)
            printf("%c ", tab->matriz[i][j]);

        printf("\n");
    }
}

// função para pintar a casa a branco
void pintarABranco(Tabuleiro *tab, int linha, char coluna)
{
    if (linha >= 0 && linha < tab->linhas && (coluna - 'a') >= 0 && (coluna - 'a') < tab->colunas)
    {
        if (tab->matriz[linha][coluna - 'a'] >= 'a' && tab->matriz[linha][coluna - 'a'] <= 'z')
            tab->matriz[linha][coluna - 'a'] = tab->matriz[linha][coluna - 'a'] - ('a' - 'A');
    }
}

// função para riscar a casa
void riscar(Tabuleiro *tab, int linha, char coluna)
{
    if (linha >= 0 && linha < tab->linhas && (coluna - 'a') >= 0 && (coluna - 'a') < tab->colunas)
        tab->matriz[linha][coluna - 'a'] = '#';
}

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
    printf("Tabuleiro lido com sucesso, ficheiro %s\n\n", nomeFicheiro);
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

// função para realizar busca em profundidade (DFS)
void dfs(Tabuleiro *tab, int linha, int coluna, int visitadas[26][26])
{
    if (linha < 0 || linha >= tab->linhas || coluna < 0 || coluna >= tab->colunas)
        return;

    if (visitadas[linha][coluna] || tab->matriz[linha][coluna] == '#')
        return;

    visitadas[linha][coluna] = 1;

    dfs(tab, linha - 1, coluna, visitadas);
    dfs(tab, linha + 1, coluna, visitadas);
    dfs(tab, linha, coluna - 1, visitadas);
    dfs(tab, linha, coluna + 1, visitadas);
}

// função para verificar se existe um caminho ortogonal entre as casas brancas (ou potencialmente brancas)
int verificarCaminho(Tabuleiro *tab)
{
    int visitadas[26][26] = {0};
    int i_inicio = -1, j_inicio = -1;

    for (int i = 0; i < tab->linhas && i_inicio == -1; i++)
    {
        for (int j = 0; j < tab->colunas && j_inicio == -1; j++)
        {
            if (tab->matriz[i][j] != '#')
            {
                i_inicio = i;
                j_inicio = j;
            }
        }
    }
    if (i_inicio == -1)
        return 1;

    dfs(tab, i_inicio, j_inicio, visitadas);

    for (int i = 0; i < tab->linhas; i++)
    {
        for (int j = 0; j < tab->colunas; j++)
        {
            if (tab->matriz[i][j] != '#' && !visitadas[i][j])
            {
                printf("Restrição violada: Não há caminho ortogonal entre a casa (%d, %c) e a casa (%d, %c)\n", i_inicio, 'a' + j_inicio, i, 'a' + j);
                return 1;
            }
        }
    }
    return 0;
}

// função para verificar as restrições
int verificarRestricoes(Tabuleiro *tab)
{
    int violacoes = 0;

    for (int i = 0; i < tab->linhas; i++)
    {
        for (int j = 0; j < tab->colunas; j++)
        {
            char casa = tab->matriz[i][j];

            if (casa == '#')
            {
                // verificar se todas as casas vizinhas (ortogonais) estão pintadas a branco
                if ((i > 0 && tab->matriz[i - 1][j] >= 'a' && tab->matriz[i - 1][j] <= 'z') ||
                    (i < tab->linhas - 1 && tab->matriz[i + 1][j] >= 'a' && tab->matriz[i + 1][j] <= 'z') ||
                    (j > 0 && tab->matriz[i][j - 1] >= 'a' && tab->matriz[i][j - 1] <= 'z') ||
                    (j < tab->colunas - 1 && tab->matriz[i][j + 1] >= 'a' && tab->matriz[i][j + 1] <= 'z'))
                {
                    printf("Restrição violada: Casa riscada (%d, %d) tem vizinhos não pintados a branco.\n", i, j);
                    violacoes = 1;
                }
            }
            else if (casa >= 'A' && casa <= 'Z')
            {
                // Verificar se há réplicas na mesma linha ou coluna
                for (int k = 0; k < tab->linhas; k++)
                {
                    if (k != i && tab->matriz[k][j] == casa)
                    {
                        printf("Restrição violada: Casa branca (%d, %d) tem réplica na linha %d.\n", i, j, k);
                        violacoes = 1;
                    }
                }
                for (int k = 0; k < tab->colunas; k++)
                {
                    if (k != j && tab->matriz[i][k] == casa)
                    {
                        printf("Restrição violada: Casa branca (%d, %d) tem réplica na coluna %d.\n", i, j, k);
                        violacoes = 1;
                    }
                }
            }
        }
    }
    if (verificarCaminho(tab))
        violacoes = 1;

    return violacoes;
}

// função auxiliar que verifica se a casa tem algum vizinho riscado
// obj : pintar de branco todas as casas vizinhas (ortogonais) de uma casa riscada
int vizinhoRiscado(Tabuleiro *tab, int linha, int coluna)
{
    if (linha > 0 && tab->matriz[linha - 1][coluna] == '#')
        return 1;
    if (linha < tab->linhas - 1 && tab->matriz[linha + 1][coluna] == '#')
        return 1;
    if (coluna > 0 && tab->matriz[linha][coluna - 1] == '#')
        return 1;
    if (coluna < tab->colunas - 1 && tab->matriz[linha][coluna + 1] == '#')
        return 1;

    return 0;
}

// função auxiliar que verifica se há alguma casa (minuscula ou maiuscula) com a mesma letra na linha ou coluna
// obj : riscar todas as letras iguais a uma letra branca na mesma linha ou coluna
int letraIgual_mesmaLinhaColuna(Tabuleiro *tab, int linha, int coluna)
{
    char letra = tab->matriz[linha][coluna];

    for (int j = 0; j < tab->colunas; j++)
    {
        if (j != coluna &&
            ((tab->matriz[linha][j] == letra) || (tab->matriz[linha][j] + ('a' - 'A') == letra)))
            return 1;
    }

    for (int i = 0; i < tab->linhas; i++)
    {
        if (i != linha &&
            ((tab->matriz[i][coluna] == letra) || (tab->matriz[i][coluna] + ('a' - 'A') == letra)))
            return 1;
    }
    return 0;
}

// função auxiliar que verifica se há alguma casa (branca/maiuscula) com a mesma letra na linha ou coluna
int casaBrancaIgual_mesmaLinhaColuna(Tabuleiro *tab, int linha, int coluna)
{
    char casa = tab->matriz[linha][coluna];

    for (int j = 0; j < tab->colunas; j++)
    {
        if (j != coluna &&
            (tab->matriz[linha][j] == toupper(casa)))
            return 1;
    }

    for (int i = 0; i < tab->linhas; i++)
    {
        if (i != linha &&
            (tab->matriz[i][coluna] == toupper(casa)))
            return 1;
    }
    return 0;
}

// função auxiliar que verifica se riscar a casa isolaria outras casas brancas
// obj : pintar de branco uma casa quando seria impossível que esta fosse riscada por isolar casas brancas
int isolaCasas(Tabuleiro *tab, int linha, int coluna)
{
    Tabuleiro temp = *tab;
    temp.matriz[linha][coluna] = '#';

    int visitadas[26][26] = {0};
    int i_inicio = -1, j_inicio = -1;

    for (int i = 0; i < temp.linhas && i_inicio == -1; i++)
    {
        for (int j = 0; j < temp.colunas && j_inicio == -1; j++)
        {
            if (temp.matriz[i][j] != '#')
            {
                i_inicio = i;
                j_inicio = j;
            }
        }
    }
    if (i_inicio == -1)
        return 0;

    dfs(&temp, i_inicio, j_inicio, visitadas);

    for (int i = 0; i < temp.linhas; i++)
    {
        for (int j = 0; j < temp.colunas; j++)
        {
            if (temp.matriz[i][j] != '#' && !visitadas[i][j])
                return 1;
        }
    }
    return 0;
}

// função para implemantar o comando 'a'
int ajudar(Tabuleiro *tab, Historico **historico)
{
    int alteracoes = 0;

    for (int i = 0; i < tab->linhas; i++)
    {
        for (int j = 0; j < tab->colunas; j++)
        {
            char c = tab->matriz[i][j];
            int casa_ignorada = (c == '#' || (c >= 'A' && c <= 'Z'));

            if (!casa_ignorada)
            {
                if (!letraIgual_mesmaLinhaColuna(tab, i, j))
                {
                    pintarABranco(tab, i, j + 'a');
                    alteracoes = 1;
                }

                if (vizinhoRiscado(tab, i, j) && !casaBrancaIgual_mesmaLinhaColuna(tab, i, j))
                {
                    pintarABranco(tab, i, j + 'a');
                    alteracoes = 1;
                }

                if (isolaCasas(tab, i, j))
                {
                    guardarHistorico(historico, tab);
                    pintarABranco(tab, i, j + 'a');
                    if (casaBrancaIgual_mesmaLinhaColuna(tab, i, j))
                        desfazer(tab, historico);
                    alteracoes = 1;
                }
                if (casaBrancaIgual_mesmaLinhaColuna(tab, i, j))
                {
                    guardarHistorico(historico, tab);
                    riscar(tab, i, j + 'a');
                    if (vizinhoRiscado(tab, i, j) || isolaCasas(tab, i, j))
                        desfazer(tab, historico);
                    alteracoes = 1;
                }
            }
        }
    }
    return alteracoes;
}

// função para implementar o comando 'a' repetidamente até não haver mais alterações
void ajudarRepetidamente(Tabuleiro *tab, Historico **historico)
{
    int alteracoes;
    do
    {
        alteracoes = ajudar(tab, historico);
    } while (alteracoes);
}