// TESTES DAS FUNÇÕES LERFICHEIRO E GUARDARFICHEIRO

#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "lerGuardar.h"

// Testar a função lerFicheiro num caso normal
void test_lerFicheiro_normal()
{
    Tabuleiro tab;
    FILE *ficheiro = fopen("tabuleiro_test.txt", "w");
    if (ficheiro == NULL)
    {
        CU_FAIL("Erro ao criar o ficheiro para teste.");
        return;
    }
    fprintf(ficheiro, "3 3\n");
    fprintf(ficheiro, "x s d\n");
    fprintf(ficheiro, "y t h\n");
    fprintf(ficheiro, "z a b\n");
    fclose(ficheiro);

    lerFicheiro(&tab, "tabuleiro_test.txt");
    CU_ASSERT_EQUAL(tab.linhas, 3);
    CU_ASSERT_EQUAL(tab.colunas, 3);
    CU_ASSERT_EQUAL(tab.matriz[0][0], 'x');
    CU_ASSERT_EQUAL(tab.matriz[0][1], 's');
    CU_ASSERT_EQUAL(tab.matriz[0][2], 'd');
    CU_ASSERT_EQUAL(tab.matriz[1][0], 'y');
    CU_ASSERT_EQUAL(tab.matriz[1][1], 't');
    CU_ASSERT_EQUAL(tab.matriz[1][2], 'h');
    CU_ASSERT_EQUAL(tab.matriz[2][0], 'z');
    CU_ASSERT_EQUAL(tab.matriz[2][1], 'a');
    CU_ASSERT_EQUAL(tab.matriz[2][2], 'b');
    remove("tabuleiro_test.txt");
}

// Testar a função lerFicheiro quando o ficheiro não existe
void test_lerFicheiro_naoExiste()
{
    Tabuleiro tab;
    char *ficheiro = "tabuleiro_inexistente.txt";
    lerFicheiro(&tab, ficheiro);
    CU_ASSERT_EQUAL(tab.linhas, 0);
    CU_ASSERT_EQUAL(tab.colunas, 0);
    CU_ASSERT_EQUAL(tab.matriz[0][0], '\0');
}

// Testar a função guardarFicheiro num caso normal
void test_guardarFicheiro_normal()
{
    Tabuleiro tab = {
        .matriz = {
            {'o', 'p', 'q'},
            {'r', 's', 't'},
            {'u', 'v', 'w'}},
        .linhas = 3,
        .colunas = 3};

    char *ficheiro = "tabuleiro_test.txt";
    guardarFicheiro(&tab, ficheiro);

    FILE *file = fopen(ficheiro, "r");
    CU_ASSERT_PTR_NOT_NULL(file);

    int linhas, colunas;
    fscanf(file, "%d %d", &linhas, &colunas);
    CU_ASSERT_EQUAL(linhas, 3);
    CU_ASSERT_EQUAL(colunas, 3);

    char matrizEsperada[3][3] = {
        {'o', 'p', 'q'},
        {'r', 's', 't'},
        {'u', 'v', 'w'}};

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            char valor;
            fscanf(file, " %c", &valor);
            CU_ASSERT_EQUAL(valor, matrizEsperada[i][j]);
        }
    }
    fclose(file);
    remove(ficheiro);
}

// Testar a função guardarFicheiro quando o tabuleiro está vazio
void test_guardarFicheiro_vazio()
{
    Tabuleiro tab = {0};

    char *ficheiro = "tabuleiro_test.txt";
    guardarFicheiro(&tab, ficheiro);

    FILE *file = fopen(ficheiro, "r");
    CU_ASSERT_PTR_NOT_NULL(file);

    int linhas, colunas;
    fscanf(file, "%d %d", &linhas, &colunas);
    CU_ASSERT_EQUAL(linhas, 0);
    CU_ASSERT_EQUAL(colunas, 0);

    fclose(file);
    remove(ficheiro);
}

int main()
{
    CU_initialize_registry();

    CU_pSuite suite_lerFicheiro = CU_add_suite("Teste de Ler Ficheiro", NULL, NULL);
    CU_add_test(suite_lerFicheiro, "Teste ler ficheiro caso normal", test_lerFicheiro_normal);
    CU_add_test(suite_lerFicheiro, "Teste ler ficheiro caso não existe", test_lerFicheiro_naoExiste);

    CU_pSuite suite_guardarFicheiro = CU_add_suite("Teste de Guardar Ficheiro", NULL, NULL);
    CU_add_test(suite_guardarFicheiro, "Teste guardar ficheiro caso normal", test_guardarFicheiro_normal);
    CU_add_test(suite_guardarFicheiro, "Teste guardar ficheiro vazio", test_guardarFicheiro_vazio);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}
