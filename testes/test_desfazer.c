// TESTES DAS FUNÇÕES DESFAZER E GUARDARHISTORICO

#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "jogo.h"

// Testar a função desfazer com tabuleiro vazio, sem histórico
void test_desfazer_vazio()
{
    Tabuleiro tab = {0};
    Historico *historico = NULL;

    desfazer(&tab, &historico);
    CU_ASSERT_EQUAL(tab.linhas, 0);
    CU_ASSERT_EQUAL(tab.colunas, 0);
    CU_ASSERT_PTR_NULL(historico);
}

// Testar a função desfazer com o tabuleiro carregado, sem mudanças
void test_desfazer_semMudanças()
{
    Tabuleiro tab = {
        .linhas = 3,
        .colunas = 3,
        .matriz = {
            {'o', 'p', 'h'},
            {'i', 'j', 'k'},
            {'l', 'm', 'n'}}};
    Historico *historico = NULL;

    guardarHistorico(&historico, &tab);
    desfazer(&tab, &historico);

    CU_ASSERT_EQUAL(tab.linhas, 3);
    CU_ASSERT_EQUAL(tab.colunas, 3);
    CU_ASSERT_PTR_NULL(historico);
}

int main()
{
    CU_initialize_registry();

    CU_pSuite suite_desfazer = CU_add_suite("Teste de Desfazer", NULL, NULL);
    CU_add_test(suite_desfazer, "Teste desfazer com tabuleiro vazio", test_desfazer_vazio);
    CU_add_test(suite_desfazer, "Teste desfazer sem mudanças", test_desfazer_semMudanças);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}