// TESTES DAS FUNÇÕES SERVALIDO E SOLVE

#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "estrutura.h"
#include "resolver.h"

void test_solve_jaResolvida()
{
    Tabuleiro tab = {
        .linhas = 5,
        .colunas = 5,
        .matriz = {
            {'E', '#', 'A', 'D', 'C'},
            {'D', 'C', '#', 'E', '#'},
            {'B', '#', 'D', 'C', 'E'},
            {'C', 'D', 'E', '#', 'B'},
            {'A', '#', 'C', 'B', '#'}}};
    int r = solve(&tab, 0, 0);
    CU_ASSERT_EQUAL(r, 1);
}

void test_solve_naoResolvido()
{
    Tabuleiro tab = {
        .linhas = 5,
        .colunas = 5,
        .matriz = {
            {'e', 'c', 'a', 'd', 'c'},
            {'d', 'c', 'd', 'e', 'c'},
            {'b', 'd', 'd', 'c', 'e'},
            {'c', 'd', 'e', 'e', 'b'},
            {'a', 'c', 'c', 'b', 'b'}}};
    int r = solve(&tab, 0, 0);
    CU_ASSERT_EQUAL(r, 1);
}

void test_solve_impossivel()
{
    Tabuleiro tab = {
        .linhas = 5,
        .colunas = 5,
        .matriz = {
            {'e', 'e', 'e', 'e', 'e'},
            {'e', 'e', 'e', 'e', 'e'},
            {'e', 'e', 'e', 'e', 'e'},
            {'e', 'e', 'e', 'e', 'e'},
            {'e', 'e', 'e', 'e', 'e'}}};
    int r = solve(&tab, 0, 0);
    CU_ASSERT_EQUAL(r, 0);
}

void test_solve_malResolvido()
{
    Tabuleiro tab = {
        .linhas = 5,
        .colunas = 5,
        .matriz = {
            {'E', '#', 'A', 'D', 'C'},
            {'#', '#', '#', 'E', '#'},
            {'B', '#', 'D', 'C', 'E'},
            {'C', 'D', 'E', '#', 'B'},
            {'A', '#', 'C', 'B', '#'}}};
    int r = solve(&tab, 0, 0);
    CU_ASSERT_EQUAL(r, 1);
}

void test_valido_DuasIguais()
{
    Tabuleiro tab = {
        .linhas = 3,
        .colunas = 3,
        .matriz = {
            {'O', 'o', 'h'},
            {'i', 'j', 'k'},
            {'l', 'm', 'n'}}};
    int r = serValido(&tab, 1, 0, 'O');
    CU_ASSERT_EQUAL(r, 0);
}

void test_valido()
{
    Tabuleiro tab = {
        .linhas = 3,
        .colunas = 3,
        .matriz = {
            {'O', 'p', 'h'},
            {'i', 'j', 'k'},
            {'l', 'm', 'n'}}};
    int r = serValido(&tab, 1, 1, '#');
    CU_ASSERT_EQUAL(r, 1);
}

void test_valido_validoMasSemCaminho()
{
    Tabuleiro tab = {
        .linhas = 3,
        .colunas = 3,
        .matriz = {
            {'O', '#', 'H'},
            {'S', 'I', 'F'},
            {'L', 'P', 'N'}}};
    int r = serValido(&tab, 1, 1, '#');
    CU_ASSERT_EQUAL(r, 0);
}

void test_valido_semCaminho()
{
    Tabuleiro tab = {
        .linhas = 3,
        .colunas = 3,
        .matriz = {
            {'O', '#', 'h'},
            {'p', '#', 'k'},
            {'l', 'm', 'n'}}};
    int r = serValido(&tab, 2, 1, '#');
    CU_ASSERT_EQUAL(r, 0);
}

int main()
{
    CU_initialize_registry();

    CU_pSuite suite_solve = CU_add_suite("Testes de Resolver", NULL, NULL);
    CU_add_test(suite_solve, "Teste de solve já resolvido", test_solve_jaResolvida);
    CU_add_test(suite_solve, "Teste de solve não resolvido", test_solve_naoResolvido);
    CU_add_test(suite_solve, "Teste de solve impossível", test_solve_impossivel);
    CU_add_test(suite_solve, "Teste de solve mal resolvido", test_solve_malResolvido);

    CU_pSuite suite_serValido = CU_add_suite("Testes de serValido", NULL, NULL);
    CU_add_test(suite_serValido, "Teste de serValido com duas iguais", test_valido_DuasIguais);
    CU_add_test(suite_serValido, "Teste de serValido", test_valido);
    CU_add_test(suite_serValido, "Teste de serValido válido mas sem caminho", test_valido_validoMasSemCaminho);
    CU_add_test(suite_serValido, "Teste de serValido sem caminho", test_valido_semCaminho);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}