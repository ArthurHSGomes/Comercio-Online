#ifndef EMISSAODENOTASFISCAIS_H
#define EMISSAODENOTASFISCAIS_H

typedef struct {
    char nome_produto[100];
    int codigo_produto;
    int quantidade;
    float preco_unitario;
    float preco_total;
} ItemVenda;

typedef struct {
    char nome[100];
    char cpf[15];
    char email[100];
    struct {
        char rua[100];
        char bairro[50];
        char cidade[50];
        char estado[3];
        char cep[10];
    } endereco;
} Comprador;

typedef struct {
    int codigo;
    ItemVenda itens[50];
    int qtd_itens;
    float total_venda;
} Venda;

float calcularFrete(float total_venda);

#endif // EMISSAODENOTASFISCAIS_H
