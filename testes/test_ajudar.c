// TESTES DAS FUNÇÕES AJUDAR, AJUDARREPETIDAMENTE E AUXILIARES

#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "ajudar.h"

// Testar função ajudar caso normal
void test_ajudar_normal()
{
    Tabuleiro tab = {
        .linhas = 3,
        .colunas = 3,
        .matriz = {
            {'#', 'a', 'b'},
            {'c', '#', 'd'},
            {'e', 'f', 'g'}}};

    int alteracoes = ajudar(&tab);

    CU_ASSERT(alteracoes >= 0);
}

// Testar funcao ajudar com todas casas já preenchidas
void test_ajudar_sem_alteracoes()
{
    Tabuleiro tab = {
        .linhas = 3,
        .colunas = 3,
        .matriz = {
            {'A', 'B', 'C'},
            {'D', 'E', 'F'},
            {'G', 'H', 'I'}}};

    int alteracoes = ajudar(&tab);

    CU_ASSERT_EQUAL(alteracoes, 0);
}

// Testar funcao ajudar com casas riscadas
void test_ajudar_casas_riscadas()
{
    Tabuleiro tab = {
        .linhas = 3,
        .colunas = 3,
        .matriz = {
            {'#', '#', '#'},
            {'#', 'a', '#'},
            {'#', '#', '#'}}};

    int alteracoes = ajudar(&tab);

    CU_ASSERT(alteracoes >= 0);
}

// Testar função ajudarRepetidamente caso normal
void test_ajudarRepetidamente_normal()
{
    Tabuleiro tab = {
        .linhas = 3,
        .colunas = 3,
        .matriz = {
            {'#', 'a', 'b'},
            {'c', '#', 'd'},
            {'e', 'f', 'g'}}};

    ajudarRepetidamente(&tab);

    CU_ASSERT(tab.matriz[0][0] == '#');
}

// Testar funcao ajudarRepetidamente sem alterações esperadas
void test_ajudarRepetidamente_semAlteracoes()
{
    Tabuleiro tab = {
        .linhas = 3,
        .colunas = 3,
        .matriz = {
            {'A', 'B', 'C'},
            {'D', 'E', 'F'},
            {'G', 'H', 'I'}}};

    ajudarRepetidamente(&tab);

    CU_ASSERT_EQUAL(tab.matriz[1][1], 'E');
}

// Testar funcao ajudarRepetidamente para nao alterar casas riscadas
void test_ajudarRepetidamente_casas_riscadas()
{
    Tabuleiro tab = {
        .linhas = 3,
        .colunas = 3,
        .matriz = {
            {'#', 'a', 'b'},
            {'c', '#', 'd'},
            {'e', 'f', 'g'}}};

    ajudarRepetidamente(&tab);

    CU_ASSERT(tab.matriz[1][1] == '#');
}

// Testar funcao casaBrancaIgual_mesmaLinhaColuna sem letra repetida na linha ou coluna
void test_sem_repeticoes()
{
    Tabuleiro tab = {
        .linhas = 3,
        .colunas = 3,
        .matriz = {
            {'A', 'B', 'C'},
            {'D', 'E', 'F'},
            {'G', 'H', 'I'}}};

    CU_ASSERT_EQUAL(casaBrancaIgual_mesmaLinhaColuna(&tab, 1, 1), 0);
}

// Testar funcao casaBrancaIgual_mesmaLinhaColuna com letra repetida na linha
void test_letra_repetida_linha()
{
    Tabuleiro tab = {
        .linhas = 3,
        .colunas = 3,
        .matriz = {
            {'A', 'A', 'C'},
            {'D', 'E', 'F'},
            {'G', 'H', 'I'}}};

    CU_ASSERT_EQUAL(casaBrancaIgual_mesmaLinhaColuna(&tab, 0, 0), 1);
}

// Testar funcao casaBrancaIgual_mesmaLinhaColuna com letra repetida na coluna
void test_letra_repetida_coluna()
{
    Tabuleiro tab = {
        .linhas = 3,
        .colunas = 3,
        .matriz = {
            {'A', 'B', 'C'},
            {'D', 'B', 'F'},
            {'G', 'B', 'I'}}};

    CU_ASSERT_EQUAL(casaBrancaIgual_mesmaLinhaColuna(&tab, 1, 1), 1);
}

// Testar função vizinhoRiscado sem vizinhos riscados
void test_vizinho_sem_riscado()
{
    Tabuleiro tab = {
        .linhas = 3,
        .colunas = 3,
        .matriz = {
            {'.', '.', '.'},
            {'.', 'X', '.'},
            {'.', '.', '.'}}};

    CU_ASSERT_EQUAL(vizinhoRiscado(&tab, 1, 1), 0);
}

// Testar função vizinhoRiscado com vizinho riscado
void test_vizinho_com_riscado()
{
    Tabuleiro tab = {
        .linhas = 3,
        .colunas = 3,
        .matriz = {
            {'.', '#', '.'},
            {'.', 'X', '.'},
            {'.', '.', '.'}}};

    CU_ASSERT_EQUAL(vizinhoRiscado(&tab, 1, 1), 1);
}

// Testar função vizinhoRiscado num canto do tabuleiro
void test_vizinho_borda()
{
    Tabuleiro tab = {
        .linhas = 3,
        .colunas = 3,
        .matriz = {
            {'#', '.', '.'},
            {'.', '.', '.'},
            {'.', '.', '.'}}};

    CU_ASSERT_EQUAL(vizinhoRiscado(&tab, 0, 0), 0);
}

// Testar funcao isolaCasas para verificar se riscar uma casa não isola outras casas brancas
void test_nao_isola_casas()
{
    Tabuleiro tab = {
        .linhas = 3,
        .colunas = 3,
        .matriz = {
            {'A', 'B', 'C'},
            {'D', 'E', 'F'},
            {'G', 'H', 'I'}}};

    CU_ASSERT_EQUAL(isolaCasas(&tab, 1, 1), 0);
}

// Testar funcao isolaCasas para verificar se riscar uma casa isola casas brancas
void test_isola_casas()
{
    Tabuleiro tab = {
        .linhas = 3,
        .colunas = 3,
        .matriz = {
            {'A', '#', 'A'},
            {'#', 'A', '#'},
            {'A', '#', 'A'}}};

    CU_ASSERT_EQUAL(isolaCasas(&tab, 1, 1), 1);
}

// Testar funcao isolaCasas para riscar um canto do tabuleiro sem isolar casas
void test_risca_borda_sem_isolar()
{
    Tabuleiro tab = {
        .linhas = 4,
        .colunas = 4,
        .matriz = {
            {'#', '.', '.', '#'},
            {'.', 'A', 'B', '.'},
            {'.', 'C', 'D', '.'},
            {'#', '.', '.', '#'}}};

    CU_ASSERT_EQUAL(isolaCasas(&tab, 2, 1), 0);
}

int main()
{
    CU_initialize_registry();

    CU_pSuite suite_ajudar = CU_add_suite("Teste de Ajudar", NULL, NULL);
    CU_add_test(suite_ajudar, "Teste de Ajudar caso normal", test_ajudar_normal);
    CU_add_test(suite_ajudar, "Teste de Ajudar sem alteracoes", test_ajudar_sem_alteracoes);
    CU_add_test(suite_ajudar, "Teste de Ajudar com casas riscadas", test_ajudar_casas_riscadas);

    CU_pSuite suite_ajudarRepetidamente = CU_add_suite("Teste de Ajudar Repetidamente", NULL, NULL);
    CU_add_test(suite_ajudarRepetidamente, "Teste de Ajudar Repetidamente caso normal", test_ajudarRepetidamente_normal);
    CU_add_test(suite_ajudarRepetidamente, "Teste de Ajudar Repetidamente sem alteracoes", test_ajudarRepetidamente_semAlteracoes);
    CU_add_test(suite_ajudarRepetidamente, "Teste de Ajudar Repetidamente com casas riscadas", test_ajudarRepetidamente_casas_riscadas);

    CU_pSuite suite_casaBrancaIgual = CU_add_suite("Teste de Casa Branca Igual na mesma linha e coluna", NULL, NULL);
    CU_add_test(suite_casaBrancaIgual, "Teste de Casa Branca Igual sem repeticoes", test_sem_repeticoes);
    CU_add_test(suite_casaBrancaIgual, "Teste de Casa Branca Igual com letra repetida na linha", test_letra_repetida_linha);
    CU_add_test(suite_casaBrancaIgual, "Teste de Casa Branca Igual com letra repetida na coluna", test_letra_repetida_coluna);

    CU_pSuite suite_vizinhoRiscado = CU_add_suite("Teste de Vizinho Riscado", NULL, NULL);
    CU_add_test(suite_vizinhoRiscado, "Teste de Vizinho Riscado sem vizinhos riscados", test_vizinho_sem_riscado);
    CU_add_test(suite_vizinhoRiscado, "Teste de Vizinho Riscado com vizinho riscado", test_vizinho_com_riscado);
    CU_add_test(suite_vizinhoRiscado, "Teste de Vizinho Riscado num canto do tabuleiro", test_vizinho_borda);

    CU_pSuite suite_isolaCasas = CU_add_suite("Teste de Isola Casas", NULL, NULL);
    CU_add_test(suite_isolaCasas, "Teste de Isola Casas para verificar se riscar uma casa não isola outras casas brancas", test_nao_isola_casas);
    CU_add_test(suite_isolaCasas, "Teste de Isola Casas para verificar se riscar uma casa isola casas brancas", test_isola_casas);
    CU_add_test(suite_isolaCasas, "Teste de Isola Casas para riscar um canto do tabuleiro sem isolar casas", test_risca_borda_sem_isolar);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}