#include "jogo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

// Testes para visualizarJogo
void test_visualizarJogo()
{
    Tabuleiro tab = {
        .matriz = {
            {'e', 'c', 'a', 'd', 'c'},
            {'d', 'c', 'd', 'e', 'c'},
            {'b', 'd', 'd', 'c', 'e'},
            {'c', 'd', 'e', 'e', 'b'},
            {'a', 'c', 'c', 'b', 'b'}},
        .linhas = 5,
        .colunas = 5};

    visualizarJogo(&tab);
    // verifica se a condicao é verdadeira
    CU_ASSERT(1); // Teste simples para verificar execução
}

// Testes para pintarABranco
void test_pintarABranco_caso_normal()
{
    Tabuleiro tab = {
        .matriz = {
            {'e', 'c', 'a', 'd', 'c'},
            {'d', 'c', 'd', 'e', 'c'},
            {'b', 'd', 'd', 'c', 'e'},
            {'c', 'd', 'e', 'e', 'b'},
            {'a', 'c', 'c', 'b', 'b'}},
        .linhas = 5,
        .colunas = 5};

    pintarABranco(&tab, 0, 'a');
    // compara valores
    CU_ASSERT_EQUAL(tab.matriz[0][0], 'E');
}

void test_pintarABranco_fora_limites()
{
    Tabuleiro tab = {
        .matriz = {
            {'e', 'c', 'a', 'd', 'c'},
            {'d', 'c', 'd', 'e', 'c'},
            {'b', 'd', 'd', 'c', 'e'},
            {'c', 'd', 'e', 'e', 'b'},
            {'a', 'c', 'c', 'b', 'b'}},
        .linhas = 5,
        .colunas = 5};

    pintarABranco(&tab, -1, 'a');
    pintarABranco(&tab, 5, 'a');
    CU_ASSERT_EQUAL(tab.matriz[0][0], 'e'); // celula permanece inalterada
}

// Testes para riscar
void test_riscar_caso_normal()
{
    Tabuleiro tab = {
        .matriz = {
            {'e', 'c', 'a', 'd', 'c'},
            {'d', 'c', 'd', 'e', 'c'},
            {'b', 'd', 'd', 'c', 'e'},
            {'c', 'd', 'e', 'e', 'b'},
            {'a', 'c', 'c', 'b', 'b'}},
        .linhas = 5,
        .colunas = 5};

    riscar(&tab, 0, 'a');
    CU_ASSERT_EQUAL(tab.matriz[0][0], '#');
}

void test_riscar_fora_limites()
{
    Tabuleiro tab = {
        .matriz = {
            {'e', 'c', 'a', 'd', 'c'},
            {'d', 'c', 'd', 'e', 'c'},
            {'b', 'd', 'd', 'c', 'e'},
            {'c', 'd', 'e', 'e', 'b'},
            {'a', 'c', 'c', 'b', 'b'}},
        .linhas = 5,
        .colunas = 5};

    riscar(&tab, -1, 'a');
    riscar(&tab, 5, 'a');
    CU_ASSERT_EQUAL(tab.matriz[0][0], 'e'); // celula permanece inalterada
}

// testes para lerFicheiro
void test_lerFicheiro_existe()
{
    Tabuleiro tab;
    char *nomeFicheiro = "tabuleiro_test.txt";
    FILE *ficheiro = fopen(nomeFicheiro, "w");
    if (ficheiro == NULL)
    {
        CU_FAIL("Erro ao criar o ficheiro para teste.");
        return;
    }
    fprintf(ficheiro, "3 3\n");
    fprintf(ficheiro, "a b c\n");
    fprintf(ficheiro, "d e f\n");
    fprintf(ficheiro, "g h i\n");
    fclose(ficheiro);

    lerFicheiro(&tab, nomeFicheiro);
    // dimensões lidas corretamente
    CU_ASSERT_EQUAL(tab.linhas, 3);
    CU_ASSERT_EQUAL(tab.colunas, 3);
    // valores lidos corretamente
    CU_ASSERT_EQUAL(tab.matriz[0][0], 'a');
    CU_ASSERT_EQUAL(tab.matriz[0][1], 'b');
    CU_ASSERT_EQUAL(tab.matriz[0][2], 'c');
    CU_ASSERT_EQUAL(tab.matriz[1][0], 'd');
    CU_ASSERT_EQUAL(tab.matriz[1][1], 'e');
    CU_ASSERT_EQUAL(tab.matriz[1][2], 'f');
    CU_ASSERT_EQUAL(tab.matriz[2][0], 'g');
    CU_ASSERT_EQUAL(tab.matriz[2][1], 'h');
    CU_ASSERT_EQUAL(tab.matriz[2][2], 'i');
    // remove arquivo temporário
    remove(nomeFicheiro);
}

void test_lerFicheiro_nao_existe()
{
    Tabuleiro tab = {.linhas = 0, .colunas = 0};
    char *nomeFicheiro = "arquivo_inexistente.txt";

    lerFicheiro(&tab, nomeFicheiro);
    // dimensoes do tab nao alteradas
    CU_ASSERT_EQUAL(tab.linhas, 0);
    CU_ASSERT_EQUAL(tab.colunas, 0);
}

void test_lerFicheiro_formato_invalido()
{
    Tabuleiro tab;
    char *nomeFicheiro = "tabuleiro_invalido.txt";
    
    // Cria ficheiro inválido
    FILE *ficheiro = fopen(nomeFicheiro, "w");
    if (ficheiro == NULL)
    {
        CU_FAIL("Erro ao criar o ficheiro para teste.");
        return;
    }
    
    // Dimensões incorretas e tabuleiro não quadrado
    fprintf(ficheiro, "3 3\n");
    fprintf(ficheiro, "a b c\n");
    fprintf(ficheiro, "d e f\n");
    fprintf(ficheiro, "g h\n");
    fclose(ficheiro);

    // Chama a função lerFicheiro sem redirecionamento da saída
    // Não é necessário redirecionar para um arquivo, pode-se usar assert para capturar erros diretamente
    lerFicheiro(&tab, nomeFicheiro);

    // Verifica se a tabuleiro não foi carregado
    CU_ASSERT_EQUAL(tab.linhas, 0);
    CU_ASSERT_EQUAL(tab.colunas, 0);

    // Verifica se a mensagem de erro foi gerada corretamente
    // Aqui vamos verificar se a mensagem está correta diretamente no fluxo do código
    FILE *input = fopen("output.txt", "r");
    if (input == NULL)
    {
        CU_FAIL("Erro ao abrir o arquivo de saída.");
        remove(nomeFicheiro);
        return;
    }

    char mensagem[256] = {0};
    fread(mensagem, 1, sizeof(mensagem) - 1, input);
    fclose(input);

    // A mensagem de erro esperada
    CU_ASSERT_STRING_EQUAL(mensagem, "Erro ao ler os dados do tabuleiro.\n");

    // Remove arquivo temporário
    remove(nomeFicheiro);
    remove("output.txt");
}

// funcao verificarRestricoes
void test_maisculas_mesma_linha()
{
    Tabuleiro tab = {
        .matriz = {
            {'e', 'c', 'a', 'd', 'c'},
            {'D', 'c', 'D', 'e', 'c'},
            {'b', 'd', 'd', 'c', 'e'},
            {'c', 'd', 'e', 'e', 'b'},
            {'a', 'c', 'c', 'b', 'b'}},
        .linhas = 5,
        .colunas = 5};
    FILE *output = freopen("output.txt", "w", stdout);
    verificarRestricoes(&tab);
    fclose(output);
    FILE *input = fopen("output.txt", "r");
    if (input == NULL)
    {
        CU_FAIL("Erro ao abrir output.txt");
        return;
    }
    char restricoes[256] = {0};
    fread(restricoes, 1, 255, input);
    fclose(input);
    // verifica texto
    CU_ASSERT_STRING_EQUAL(restricoes, "Restrição violada: Casa branca (1, c) tem réplica na linha 1.\n");
}

// testes para guardarHistorico
void test_guardarHistorico_sem_historico()
{
    // histórico vazio
    Historico *historico = NULL;
    // cria um tabuleiro para adicionar ao histórico
    Tabuleiro tab = {
        .matriz = {
            {'e', 'c', 'a'},
            {'d', 'e', 'f'},
            {'g', 'h', 'i'}},
        .linhas = 3,
        .colunas = 3};

    guardarHistorico(&historico, &tab);
    // valida  historico
    CU_ASSERT_PTR_NOT_NULL(historico);
    CU_ASSERT_EQUAL(historico->tabAnterior.linhas, 3);
    CU_ASSERT_EQUAL(historico->tabAnterior.colunas, 3);
    CU_ASSERT_EQUAL(historico->tabAnterior.matriz[0][0], 'e');
    CU_ASSERT_PTR_NULL(historico->anterior);

    while (historico != NULL)
    {
        Historico *temp = historico;
        historico = historico->anterior;
        free(temp);
    }
}

void test_guardarHistorico_com_mudancas()
{
    // historico vazio
    Historico *historico = NULL;
    // tabs com mudanças
    Tabuleiro tab1 = {
        .matriz = {
            {'a', 'b', 'c'},
            {'d', 'e', 'f'},
            {'g', 'h', 'i'}},
        .linhas = 3,
        .colunas = 3};
    guardarHistorico(&historico, &tab1);

    Tabuleiro tab2 = {
        .matriz = {
            {'A', 'B', 'C'},
            {'D', 'E', 'F'},
            {'G', 'H', 'I'}},
        .linhas = 3,
        .colunas = 3};
    guardarHistorico(&historico, &tab2);

    Tabuleiro tab3 = {
        .matriz = {
            {'1', '2', '3'},
            {'4', '5', '6'},
            {'7', '8', '9'}},
        .linhas = 3,
        .colunas = 3};
    guardarHistorico(&historico, &tab3);
    // valida historico para tab3
    CU_ASSERT_PTR_NOT_NULL(historico);
    CU_ASSERT_EQUAL(historico->tabAnterior.linhas, 3);
    CU_ASSERT_EQUAL(historico->tabAnterior.colunas, 3);
    CU_ASSERT_EQUAL(historico->tabAnterior.matriz[0][0], '1');
    CU_ASSERT_EQUAL(historico->tabAnterior.matriz[2][2], '9');
    // valida historico para tab2
    CU_ASSERT_PTR_NOT_NULL(historico->anterior);
    CU_ASSERT_EQUAL(historico->anterior->tabAnterior.matriz[0][0], 'A');
    CU_ASSERT_EQUAL(historico->anterior->tabAnterior.matriz[2][2], 'I');
    // valida historico para tab1
    CU_ASSERT_PTR_NOT_NULL(historico->anterior->anterior);
    CU_ASSERT_EQUAL(historico->anterior->anterior->tabAnterior.matriz[0][0], 'a');
    CU_ASSERT_EQUAL(historico->anterior->anterior->tabAnterior.matriz[2][2], 'i');
    // historico termina apos primeiro elemento
    CU_ASSERT_PTR_NULL(historico->anterior->anterior->anterior);

    while (historico != NULL)
    {
        Historico *temp = historico;
        historico = historico->anterior;
        free(temp);
    }
}

// testes para guardarFicheiro
void test_guardarFicheiro_sem_tabuleiro_carregado()
{
    Tabuleiro tab = {0}; // tabuleiro não carregado
    char *nomeFicheiro = "tabuleiro_vazio.txt";

    FILE *output = freopen("output.txt", "w", stdout);
    guardarFicheiro(&tab, nomeFicheiro);
    fclose(output);
    // verifica se arquivo foi criado
    FILE *ficheiro = fopen(nomeFicheiro, "r");
    CU_ASSERT_PTR_NOT_NULL(ficheiro); // confirma que o arquivo foi criado

    int linhas = 0, colunas = 0;
    int resultado = fscanf(ficheiro, "%d %d", &linhas, &colunas);
    fclose(ficheiro);
    // conteudo invalido (tab nao carregado)
    CU_ASSERT_EQUAL(resultado, EOF);
    CU_ASSERT_EQUAL(linhas, 0);
    CU_ASSERT_EQUAL(colunas, 0);

    FILE *input = fopen("output.txt", "r");
    char mensagem[256] = {0};
    fread(mensagem, 1, sizeof(mensagem) - 1, input);
    fclose(input);
    CU_ASSERT_STRING_EQUAL(mensagem, "Tabuleiro guardado com sucesso no ficheiro tabuleiro_vazio.txt\n\n");
    // limpa arquivos temporários
    remove(nomeFicheiro);
    remove("output.txt");
}

void test_guardarFicheiro_com_mudancas()
{
    Tabuleiro tab = {
        .matriz = {
            {'a', 'b', 'c'},
            {'d', 'e', 'f'},
            {'g', 'h', 'i'}},
        .linhas = 3,
        .colunas = 3};
    char *nomeFicheiro = "tabuleiro_mudancas.txt";
    // mudanças no tab
    tab.matriz[0][0] = 'x';
    tab.matriz[1][1] = 'y';
    tab.matriz[2][2] = 'z';
    // guarda tabuleiro alterado no arquivo
    guardarFicheiro(&tab, nomeFicheiro);

    FILE *ficheiro = fopen(nomeFicheiro, "r");
    CU_ASSERT_PTR_NOT_NULL(ficheiro); // confirma que o arquivo foi criado
    int linhas = 0, colunas = 0;
    fscanf(ficheiro, "%d %d", &linhas, &colunas);

    CU_ASSERT_EQUAL(linhas, 3);
    CU_ASSERT_EQUAL(colunas, 3);

    char matriz_lida[3][3];
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            fscanf(ficheiro, " %c", &matriz_lida[i][j]);
        }
    }
    fclose(ficheiro);
    // verifica mudanças feitas no tab
    CU_ASSERT_EQUAL(matriz_lida[0][0], 'x');
    CU_ASSERT_EQUAL(matriz_lida[1][1], 'y');
    CU_ASSERT_EQUAL(matriz_lida[2][2], 'z');
    CU_ASSERT_EQUAL(matriz_lida[0][1], 'b');
    CU_ASSERT_EQUAL(matriz_lida[1][0], 'd');
    CU_ASSERT_EQUAL(matriz_lida[2][1], 'h');
    // limpa arquivo gerado
    remove(nomeFicheiro);
}

// teste para desfazer
void test_desfazer_sem_tab()
{
    Tabuleiro tab;
    Historico *historico = NULL; // sem tabuleiro carregado
    tab.linhas = 10;
    tab.colunas = 10;
    for (int i = 0; i < tab.linhas; i++)
    {
        for (int j = 0; j < tab.colunas; j++)
        {
            tab.matriz[i][j] = '.';
        }
    }
    desfazer(&tab, &historico);
    CU_ASSERT_PTR_NULL(historico);
    CU_ASSERT_EQUAL(tab.linhas, 10);
    CU_ASSERT_EQUAL(tab.colunas, 10);
    for (int i = 0; i < tab.linhas; i++)
    {
        for (int j = 0; j < tab.colunas; j++)
        {
            CU_ASSERT_EQUAL(tab.matriz[i][j], '.');
        }
    }
}

// testes para verificarRestricoes
void test_verificarRestricoes_tabuleiro_valido()
{
    Tabuleiro tab = {
        .matriz = {
            {'A', '#', 'B'},
            {'#', 'C', '#'},
            {'D', '#', 'E'}},
        .linhas = 3,
        .colunas = 3};

    FILE *output = freopen("output.txt", "w", stdout);

    verificarRestricoes(&tab);
    fclose(output);
    // le conteudo do ficheiro
    FILE *input = fopen("output.txt", "r");
    char mensagem[256] = {0};
    fread(mensagem, 1, sizeof(mensagem) - 1, input);
    fclose(input);

    CU_ASSERT_STRING_EQUAL(mensagem, ""); // output deve ser vazio para tab valido
    // remove arquivo temporario
    remove("output.txt");
}

void test_verificarRestricoes_violacao_regra1()
{
    Tabuleiro tab = {
        .matriz = {
            {'A', 'B', 'C'},
            {'D', 'D', 'F'},
            {'G', 'H', 'I'}},
        .linhas = 3,
        .colunas = 3};

    FILE *output = freopen("output.txt", "w", stdout);

    verificarRestricoes(&tab);
    fclose(output);
    // le conteudo do ficheiro
    FILE *input = fopen("output.txt", "r");
    if (input == NULL)
    {
        CU_FAIL("Erro ao abrir arquivo de saída");
        return;
    }
    char mensagem[256] = {0};
    fread(mensagem, 1, sizeof(mensagem) - 1, input);
    fclose(input);

    CU_ASSERT_STRING_EQUAL(
        mensagem,
        "Restrição violada: Casa branca (1, 1) tem réplica na linha 1.\n");
    // remove arquivo temporario
    remove("output.txt");
}

void test_verificarRestricoes_violacao_regra2()
{
    Tabuleiro tab = {
        .matriz = {
            {'X', 'Y', 'Z'},
            {'A', 'Y', 'C'},
            {'D', 'Y', 'F'}},
        .linhas = 3,
        .colunas = 3};

    FILE *output = freopen("output.txt", "w", stdout);

    verificarRestricoes(&tab);
    fclose(output);
    // le conteudo do ficheiro
    FILE *input = fopen("output.txt", "r");
    if (input == NULL)
    {
        CU_FAIL("Erro ao abrir arquivo de saída");
        return;
    }

    char mensagem[256] = {0};
    fread(mensagem, 1, sizeof(mensagem) - 1, input);
    fclose(input);

    CU_ASSERT_STRING_EQUAL(
        mensagem,
        "Restrição violada: Casa branca (0, 1) tem réplica na coluna 1.\n");
    // remove arquivo temporario
    remove("output.txt");
}

void test_verificarRestricoes_violacao_regra3()
{
    Tabuleiro tab = {
        .matriz = {
            {'A', '#', 'b'},
            {'#', 'c', '#'},
            {'d', '#', 'E'}},
        .linhas = 3,
        .colunas = 3};

    FILE *output = freopen("output.txt", "w", stdout);

    verificarRestricoes(&tab);
    fclose(output);
    // le conteudo do ficheiro
    FILE *input = fopen("output.txt", "r");
    if (input == NULL)
    {
        CU_FAIL("Erro ao abrir arquivo de saída");
        return;
    }

    char mensagem[256] = {0};
    fread(mensagem, 1, sizeof(mensagem) - 1, input);
    fclose(input);

    CU_ASSERT_STRING_EQUAL(mensagem, "Restrição violada: Casa riscada (0, 1) tem vizinhos não pintados a branco.\n");
    // remove arquivo temporario
    remove("output.txt");
}

void test_verificarRestricoes_vizinhos_validos()
{
    Tabuleiro tab = {
        .matriz = {
            {'A', '#', 'C'},
            {'#', 'D', '#'},
            {'E', '#', 'F'}},
        .linhas = 3,
        .colunas = 3};

    FILE *output = freopen("output.txt", "w", stdout);

    verificarRestricoes(&tab);
    fclose(output);
    // le conteudo do ficheiro
    FILE *input = fopen("output.txt", "r");
    if (input == NULL)
    {
        CU_FAIL("Erro ao abrir arquivo de saída");
        return;
    }

    char mensagem[256] = {0};
    fread(mensagem, 1, sizeof(mensagem) - 1, input);
    fclose(input);

    CU_ASSERT_STRING_EQUAL(mensagem, ""); // tab sem violaçoes
    // remove arquivo temporario
    remove("output.txt");
}

void test_verificarRestricoes_tabuleiro_vazio()
{
    // tab vazio
    Tabuleiro tab = {
        .matriz = {{0}}, // matriz vazia
        .linhas = 0,
        .colunas = 0};

    FILE *output = freopen("output.txt", "w", stdout);

    verificarRestricoes(&tab);
    fclose(output);

    FILE *input = fopen("output.txt", "r");
    if (input == NULL)
    {
        CU_FAIL("Erro ao abrir arquivo de saída");
        return;
    }

    char mensagem[256] = {0};
    fread(mensagem, 1, sizeof(mensagem) - 1, input);
    fclose(input);

    CU_ASSERT_STRING_EQUAL(mensagem, ""); // tab vazio
    // remove arquivo temporario
    remove("output.txt");
}

int main()
{
    CU_initialize_registry(); // inicializa registo dos testes no CUnit

    // Suite para visualizarJogo
    // suite agrupa testes relacionados
    // NULL (não há funções específicas para inicialização ou limpeza da suíte)
    CU_pSuite suite_visualizarJogo = CU_add_suite("Suite_VisualizarJogo", NULL, NULL);
    // teste individual
    CU_add_test(suite_visualizarJogo, "Teste visualizarJogo", test_visualizarJogo);

    // Suite para pintarABranco
    CU_pSuite suite_pintarABranco = CU_add_suite("Suite_PintarABranco", NULL, NULL);
    CU_add_test(suite_pintarABranco, "Teste pintarABranco caso normal", test_pintarABranco_caso_normal);
    CU_add_test(suite_pintarABranco, "Teste pintarABranco fora dos limites", test_pintarABranco_fora_limites);

    // Suite para riscar
    CU_pSuite suite_riscar = CU_add_suite("Suite_Riscar", NULL, NULL);
    CU_add_test(suite_riscar, "Teste riscar caso normal", test_riscar_caso_normal);
    CU_add_test(suite_riscar, "Teste riscar fora dos limites", test_riscar_fora_limites);

    CU_pSuite suite_lerFicheiro = CU_add_suite("Suite_LerFicheiro", NULL, NULL);
    CU_add_test(suite_lerFicheiro, "Teste lerFicheiro com ficheiro existente", test_lerFicheiro_existe);
    CU_add_test(suite_lerFicheiro, "Teste lerFicheiro arquivo inexistente", test_lerFicheiro_nao_existe);
    CU_add_test(suite_lerFicheiro, "Teste lerFicheiro com formato inválido", test_lerFicheiro_formato_invalido);

    CU_pSuite suite_historico = CU_add_suite("Suite_GuardarHistorico", NULL, NULL);
    CU_add_test(suite_historico, "Teste guardarHistorico sem histórico", test_guardarHistorico_sem_historico);
    CU_add_test(suite_historico, "Teste guardarHistorico com mudanças", test_guardarHistorico_com_mudancas);

    CU_pSuite suite_guardarFicheiro = CU_add_suite("Suite_GuardarFicheiro", NULL, NULL);
    // CU_add_test(suite_guardarFicheiro, "Teste guardarFicheiro sem tabuleiro carregado", test_guardarFicheiro_sem_tabuleiro_carregado);
    CU_add_test(suite_guardarFicheiro, "Teste guardarFicheiro com mudanças", test_guardarFicheiro_com_mudancas);

    CU_pSuite suite_desfazer = CU_add_suite("Suite_Desfazer", NULL, NULL);
    CU_add_test(suite_desfazer, "Teste desfazer sem histórico", test_desfazer_sem_tab);

    CU_pSuite suite_verificarRestricoes = CU_add_suite("Suite_VerificarRestricoes", NULL, NULL);
    CU_add_test(suite_verificarRestricoes, "Teste verificarRestricoes tabuleiro válido", test_verificarRestricoes_tabuleiro_valido);
    CU_add_test(suite_verificarRestricoes, "Teste verificarRestricoes violação regra 1", test_verificarRestricoes_violacao_regra1);
    CU_add_test(suite_verificarRestricoes, "Teste verificarRestricoes violação regra 2 com matriz nova", test_verificarRestricoes_violacao_regra2);
    CU_add_test(suite_verificarRestricoes, "Teste verificarRestricoes violação regra 3", test_verificarRestricoes_violacao_regra3);
    CU_add_test(suite_verificarRestricoes, "Teste verificarRestricoes vizinhos válidos", test_verificarRestricoes_vizinhos_validos);
    CU_add_test(suite_verificarRestricoes, "Teste verificarRestricoes tabuleiro vazio", test_verificarRestricoes_tabuleiro_vazio);

    CU_basic_set_mode(CU_BRM_VERBOSE); // modo básico de execução de testes no CUnit
    CU_basic_run_tests();              // executa todos os testes definidos nas suítes criadas
    CU_cleanup_registry();             // evitar vazamento de memória após os testes

    return 0; // programa executado com sucesso
}