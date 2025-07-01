#include "munit.h"
#include "emissaodenotasficais.h"
#include <string.h>
#include <stdio.h>


float calcularFrete(float total_venda);


static MunitResult test_calcular_frete(const MunitParameter params[], void* data) {
    munit_assert_float(calcularFrete(50.0f), ==, 30.0f);
    munit_assert_float(calcularFrete(150.0f), ==, 20.0f);
    munit_assert_float(calcularFrete(350.0f), ==, 0.0f);
    return MUNIT_OK;
}


static MunitResult test_total_venda(const MunitParameter params[], void* data) {
    Venda v = {0};
    v.qtd_itens = 2;
    v.itens[0].quantidade = 2;
    v.itens[0].preco_unitario = 10.0f;
    v.itens[0].preco_total = v.itens[0].quantidade * v.itens[0].preco_unitario;
    v.itens[1].quantidade = 3;
    v.itens[1].preco_unitario = 20.0f;
    v.itens[1].preco_total = v.itens[1].quantidade * v.itens[1].preco_unitario;
    v.total_venda = v.itens[0].preco_total + v.itens[1].preco_total;
    munit_assert_float(v.total_venda, ==, 80.0f);
    return MUNIT_OK;
}

static MunitTest tests[] = {
    {"/calcular_frete", test_calcular_frete, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/total_venda", test_total_venda, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};

static const MunitSuite suite = {
    "./emissaodenotasficais-tests",
    tests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
