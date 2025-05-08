// TESTES DA FUNÇÃO VERIFICARRESTRIÇÕES

#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "verificar.h"

// Testar a função verificarRestricoes num caso normal
void test_verificarRestricoes()
{
    Tabuleiro tab = {
        .linhas = 3,
        .colunas = 3,
        .matriz = {
            {'A', 'B', 'C'},
            {'#', 'E', 'F'},
            {'G', 'H', 'I'}}};

    int r = verificarRestricoes(&tab);
    CU_ASSERT_EQUAL(r, 0);
}

// Testar a função verificarRestricoes com mais de uma casa branca na mesma linha
void test_verificarRestricoes_regrasCasasBrancas_linha()
{
    Tabuleiro tab = {
        .linhas = 3,
        .colunas = 3,
        .matriz = {
            {'X', 'D', 'C'},
            {'#', 'E', 'F'},
            {'X', 'H', 'I'}}};

    int r = verificarRestricoes(&tab);
    CU_ASSERT_EQUAL(r, 1);
}

// Testar a função verificarRestricoes com mais de uma casa branca na mesma coluna
void test_verificarRestricoes_regrasCasasBrancas_coluna()
{
    Tabuleiro tab = {
        .linhas = 3,
        .colunas = 3,
        .matriz = {
            {'O', 'D', 'C'},
            {'A', 'E', 'C'},
            {'S', 'H', 'I'}}};
    int r = verificarRestricoes(&tab);
    CU_ASSERT_EQUAL(r, 1);
}

// Testar a função verificarRestricoes onde a regra das casas riscadas não é respeitada
void test_verificarRestricoes_regrasCasasRiscadas()
{
    Tabuleiro tab = {
        .linhas = 3,
        .colunas = 3,
        .matriz = {
            {'#', 'd', 'c'},
            {'g', 'e', 'f'},
            {'#', 'h', 'i'}}};

    int r = verificarRestricoes(&tab);
    CU_ASSERT_EQUAL(r, 1);
}

// Testar a função verificarRestricoes onde a regra das casas riscadas é respeitada
void test_verificarRestricoes_regrasCasasRiscadas_respeitada()
{
    Tabuleiro tab = {
        .linhas = 3,
        .colunas = 3,
        .matriz = {
            {'#', 'D', 'c'},
            {'G', '#', 'F'},
            {'h', 'I', 'j'}}};

    int r = verificarRestricoes(&tab);
    CU_ASSERT_EQUAL(r, 0);
}

// Testar a função verificarRestricoes com um tabuleiro vazio
void test_verificarRestricoes_tabuleiroVazio()
{
    Tabuleiro tab = {0};
    int r = verificarRestricoes(&tab);
    CU_ASSERT_EQUAL(r, 1);
}

// Testar a função verificarRestricoes com um caminho incorreto
void test_verificarRestricoes_caminho_incorreto()
{
    Tabuleiro tab = {
        .linhas = 3,
        .colunas = 3,
        .matriz = {
            {'A', '#', '#'},
            {'#', 'E', '#'},
            {'G', '#', '#'}}};

    int r = verificarRestricoes(&tab);
    CU_ASSERT_EQUAL(r, 1);
}

int main()
{
    CU_initialize_registry();
    CU_pSuite suite_verificarRestrições = CU_add_suite("Teste de Verificar Retrições", NULL, NULL);

    CU_add_test(suite_verificarRestrições, "test_verificarRestricoes", test_verificarRestricoes);
    CU_add_test(suite_verificarRestrições, "test_verificarRestricoes_regrasCasasBrancas_linha", test_verificarRestricoes_regrasCasasBrancas_linha);
    CU_add_test(suite_verificarRestrições, "test_verificarRestricoes_regrasCasasBrancas_coluna", test_verificarRestricoes_regrasCasasBrancas_coluna);
    CU_add_test(suite_verificarRestrições, "test_verificarRestricoes_regrasCasasRiscadas", test_verificarRestricoes_regrasCasasRiscadas);
    CU_add_test(suite_verificarRestrições, "test_verificarRestricoes_regrasCasasRiscadas_respeitada", test_verificarRestricoes_regrasCasasRiscadas_respeitada);
    CU_add_test(suite_verificarRestrições, "test_verificarRestricoes_tabuleiroVazio", test_verificarRestricoes_tabuleiroVazio);
    CU_add_test(suite_verificarRestrições, "test_verificarRestricoes_caminho_incorreto", test_verificarRestricoes_caminho_incorreto);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}