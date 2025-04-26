// TESTES DAS FUNÇÕES PINTAR A BRANCO E RISCAR

#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "jogo.h"

// Testar a função pintarABranco num caso normal
void test_pintarABranco()
{
    Tabuleiro tab = {
        .linhas = 3,
        .colunas = 3,
        .matriz = {
            {'a', 'b', 'c'},
            {'d', 'e', 'f'},
            {'g', 'h', 'i'}}};

    pintarABranco(&tab, 0, 'b');
    CU_ASSERT_EQUAL(tab.matriz[0][1], 'B');
}

// Testar a função pintarABranco com tabuleiro vazio
void test_pintarABranco_vazio()
{
    Tabuleiro tab = {0};
    pintarABranco(&tab, 0, 'a');
    CU_ASSERT_EQUAL(tab.matriz[0][0], 0);
}

// Testar a função pintarABranco quando a coordenada está fora dos limites
void test_pintarABranco_foraLimites()
{
    Tabuleiro tab = {
        .linhas = 3,
        .colunas = 3,
        .matriz = {
            {'e', 'h', 'i'},
            {'j', 'k', 'l'},
            {'m', 'n', 'o'}}};
    pintarABranco(&tab, -1, 'a');
    CU_ASSERT_EQUAL(tab.matriz[0][0], 'e');
}

// Testar a função pintarABranco quando a casa já está riscada
void test_pintarABranco_riscada()
{
    Tabuleiro tab = {
        .linhas = 3,
        .colunas = 3,
        .matriz = {
            {'#', 'y', 'z'},
            {'a', 'b', 'c'},
            {'d', 'e', 'f'}}};

    pintarABranco(&tab, 0, 'a');
    CU_ASSERT_EQUAL(tab.matriz[0][0], '#');
}

// Testar a função pintarABranco quando a casa já está pintada
void test_pintarABranco_pintada()
{
    Tabuleiro tab = {
        .linhas = 3,
        .colunas = 3,
        .matriz = {
            {'A', 'w', 'x'},
            {'y', 'z', 'a'},
            {'b', 'c', 'd'}}};
    pintarABranco(&tab, 0, 'a');
    CU_ASSERT_EQUAL(tab.matriz[0][0], 'A');
}

// Testar a função riscar num caso normal
void test_riscar()
{
    Tabuleiro tab = {
        .linhas = 3,
        .colunas = 3,
        .matriz = {
            {'b', 'u', 'v'},
            {'w', 'x', 'y'},
            {'z', 'a', 'b'}}};

    riscar(&tab, 0, 'b');
    CU_ASSERT_EQUAL(tab.matriz[0][1], '#');
}

// Testar a função riscar com tabuleiro vazio
void test_riscar_vazio()
{
    Tabuleiro tab = {0};
    riscar(&tab, 0, 'a');
    CU_ASSERT_EQUAL(tab.matriz[0][0], 0);
}

// Testar a função riscar quando a coordenada está fora dos limites
void test_riscar_fora_limites()
{
    Tabuleiro tab = {
        .linhas = 3,
        .colunas = 3,
        .matriz = {
            {'b', 'p', 'q'},
            {'r', 's', 't'},
            {'u', 'v', 'w'}}};

    riscar(&tab, -1, 'b');
    CU_ASSERT_EQUAL(tab.matriz[0][0], 'b');
}

// Testar a função riscar quando a casa já está riscada
void test_riscar_riscada()
{
    Tabuleiro tab = {
        .linhas = 3,
        .colunas = 3,
        .matriz = {
            {'#', 'j', 'k'},
            {'l', 'm', 'n'},
            {'o', 'p', 'q'}}};

    riscar(&tab, 0, 'a');
    CU_ASSERT_EQUAL(tab.matriz[0][0], '#');
}

// Testar a função riscar quando a casa já está pintada
void test_riscar_pintada()
{
    Tabuleiro tab = {
        .linhas = 3,
        .colunas = 3,
        .matriz = {
            {'X', 'y', 'z'},
            {'a', 'b', 'c'},
            {'d', 'e', 'f'}}};

    riscar(&tab, 0, 'a');
    CU_ASSERT_EQUAL(tab.matriz[0][0], '#');
}

int main()
{
    CU_initialize_registry();

    CU_pSuite suite_pintarABranco = CU_add_suite("Testes de Pintar a Branco", NULL, NULL);
    CU_add_test(suite_pintarABranco, "Testar pintar a branco caso normal", test_pintarABranco);
    CU_add_test(suite_pintarABranco, "Testar pintar a branco com tabuleiro vazio", test_pintarABranco_vazio);
    CU_add_test(suite_pintarABranco, "Testar pintar a branco fora dos limites", test_pintarABranco_foraLimites);
    CU_add_test(suite_pintarABranco, "Testar pintar a branco casa já riscada", test_pintarABranco_riscada);
    CU_add_test(suite_pintarABranco, "Testar pintar a branco casa já pintada", test_pintarABranco_pintada);

    CU_pSuite suite_riscar = CU_add_suite("Testes de Riscar", NULL, NULL);
    CU_add_test(suite_riscar, "Testar riscar caso normal", test_riscar);
    CU_add_test(suite_riscar, "Testar riscar com tabuleiro vazio", test_riscar_vazio);
    CU_add_test(suite_riscar, "Testar riscar fora dos limites", test_riscar_fora_limites);
    CU_add_test(suite_riscar, "Testar riscar casa já riscada", test_riscar_riscada);
    CU_add_test(suite_riscar, "Testar riscar casa já pintada", test_riscar_pintada);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}
