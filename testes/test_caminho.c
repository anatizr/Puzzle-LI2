// TESTES DA FUNÇÃO VERIFICARCAMINHOORTOGONAL

#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "jogo.h"

// Testar função dfs num caso normal
void test_dfs_normal()
{
    Tabuleiro tab = {
        .linhas = 3,
        .colunas = 3,
        .matriz = {
            {'a', 'g', 'c'},
            {'#', '#', 'f'},
            {'e', 'h', 'i'}}};

    int visitadas[26][26] = {0};
    dfs(&tab, 0, 0, visitadas);
    CU_ASSERT_EQUAL(visitadas[0][0], 1);
    CU_ASSERT_EQUAL(visitadas[0][1], 1);
    CU_ASSERT_EQUAL(visitadas[0][2], 1);
    CU_ASSERT_EQUAL(visitadas[1][0], 0);
    CU_ASSERT_EQUAL(visitadas[1][1], 0);
    CU_ASSERT_EQUAL(visitadas[1][2], 1);
    CU_ASSERT_EQUAL(visitadas[2][0], 1);
    CU_ASSERT_EQUAL(visitadas[2][1], 1);
    CU_ASSERT_EQUAL(visitadas[2][2], 1);
}

// Testar função dfs com casa isolada
void test_dfs_casaIsolada()
{
    Tabuleiro tab = {
        .linhas = 3,
        .colunas = 3,
        .matriz = {
            {'#', '#', '#'},
            {'#', 'a', '#'},
            {'#', '#', '#'}}};

    int visitadas[26][26] = {0};
    dfs(&tab, 1, 1, visitadas);
    CU_ASSERT_EQUAL(visitadas[0][0], 0);
    CU_ASSERT_EQUAL(visitadas[0][1], 0);
    CU_ASSERT_EQUAL(visitadas[0][2], 0);
    CU_ASSERT_EQUAL(visitadas[1][0], 0);
    CU_ASSERT_EQUAL(visitadas[1][1], 1);
    CU_ASSERT_EQUAL(visitadas[1][2], 0);
    CU_ASSERT_EQUAL(visitadas[2][0], 0);
    CU_ASSERT_EQUAL(visitadas[2][1], 0);
    CU_ASSERT_EQUAL(visitadas[2][2], 0);
}

// Testar função dfs com coordenadas fora dos limites
void test_dfs_foraLimites()
{
    Tabuleiro tab = {
        .linhas = 3,
        .colunas = 3,
        .matriz = {
            {'#', 'h', 'o'},
            {'t', 'u', 'v'},
            {'w', '#', 'y'}}};

    int visitadas[26][26] = {0};

    dfs(&tab, -1, 0, visitadas);
    dfs(&tab, 0, -1, visitadas);
    dfs(&tab, 3, 0, visitadas);
    dfs(&tab, 0, 3, visitadas);

    CU_ASSERT_EQUAL(visitadas[0][0], 0);
    CU_ASSERT_EQUAL(visitadas[0][1], 0);
    CU_ASSERT_EQUAL(visitadas[1][0], 0);
    CU_ASSERT_EQUAL(visitadas[2][1], 0);
}

// Testar função verificarCaminho com caminho não conectado
void test_verificar_caminho_nao_connectado()
{
    Tabuleiro tab = {
        .linhas = 3,
        .colunas = 3,
        .matriz = {
            {'O', '#', 'C'},
            {'#', 'B', 'C'},
            {'S', 'H', 'I'}}};
    int c = verificarCaminho(&tab);
    CU_ASSERT_EQUAL(c, 1);
}

void test_verificar_caminho_valido()
{
    Tabuleiro tab = {
        .linhas = 3,
        .colunas = 3,
        .matriz = {
            {'O', 'B', 'C'},
            {'#', 'D', 'C'},
            {'S', 'H', 'I'}}};
    int c = verificarCaminho(&tab);
    CU_ASSERT_EQUAL(c, 0);
}

int main()
{
    CU_initialize_registry();

    CU_pSuite suite_dfs = CU_add_suite("Testes de dfs", NULL, NULL);
    CU_add_test(suite_dfs, "Teste de dfs caso normal", test_dfs_normal);
    CU_add_test(suite_dfs, "Teste de dfs casa isolada", test_dfs_casaIsolada);
    CU_add_test(suite_dfs, "Teste de dfs fora dos limites", test_dfs_foraLimites);

    CU_pSuite suite_verificarCaminho = CU_add_suite("Teste de Verificar o Caminho", NULL, NULL);
    CU_add_test(suite_verificarCaminho, "Teste de Caminho Invalido", test_verificar_caminho_nao_connectado);
    CU_add_test(suite_verificarCaminho, "Teste Verificar Caminho Valido", test_verificar_caminho_valido);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}