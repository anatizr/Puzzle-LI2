// TESTES DA FUNÇÃO VISUALIZARJOGO

#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "base.h"

// Função auxiliar para verificar a saída
void verificarSaida(Tabuleiro *tab, const char *esperado[])
{
    freopen("output.txt", "w", stdout);
    visualizarJogo(tab);
    freopen("/dev/tty", "w", stdout);
    FILE *file = fopen("output.txt", "r");
    CU_ASSERT_PTR_NOT_NULL(file);

    if (file)
    {
        for (int i = 0; esperado[i] != NULL; i++)
        {
            char linha[50];
            fgets(linha, sizeof(linha), file);
            CU_ASSERT_STRING_EQUAL(linha, esperado[i]);
        }
        fclose(file);
        remove("output.txt");
    }
}

// Testar a função visualizarJogo num caso normal
void test_visualizarJogo_normal()
{
    Tabuleiro tab = {
        .linhas = 3,
        .colunas = 3,
        .matriz = {
            {'a', 'b', 'c'},
            {'d', 'e', 'f'},
            {'g', 'h', 'i'}}};

    const char *esperado[] = {
        "a b c \n",
        "d e f \n",
        "g h i \n",
        NULL};
    verificarSaida(&tab, esperado);
}

// Testar a função visualizarJogo com um tabuleiro vazio
void test_visualizarJogo_vazio()
{
    Tabuleiro tab = {0};
    const char *esperado[] = {NULL};

    verificarSaida(&tab, esperado);
}

// Testar a função visualizarJogo com símbolos
void test_visualizarJogo_simbolos()
{
    Tabuleiro tab = {
        .linhas = 3,
        .colunas = 3,
        .matriz = {
            {'A', '#', 'B'},
            {'#', 'C', '#'},
            {'D', '#', 'F'}}};

    const char *esperado[] = {
        "A # B \n",
        "# C # \n",
        "D # F \n",
        NULL};

    verificarSaida(&tab, esperado);
}

int main()
{
    CU_initialize_registry();

    CU_pSuite suite_visualizarJogo = CU_add_suite("Teste de Visualizar o Jogo", NULL, NULL);
    CU_add_test(suite_visualizarJogo, "Teste visualizar tabuleiro caso normal", test_visualizarJogo_normal);
    CU_add_test(suite_visualizarJogo, "Teste visualizar tabuleiro vazio", test_visualizarJogo_vazio);
    CU_add_test(suite_visualizarJogo, "Teste visualizar tabuleiro com símbolos", test_visualizarJogo_simbolos);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}
