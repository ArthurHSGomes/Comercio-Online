// Modulo: Emissao da Nota Fiscal
// Responsavel: Arthur Henrique Gomes

#include <stdio.h>
#include <string.h>

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

float calcularFrete(float total_venda) {
    if (total_venda <= 100.0f) return 30.0f;
    if (total_venda <= 300.0f) return 20.0f;
    return 0.0f;
}

void emitirNotaFiscal(Venda venda, Comprador comprador) {
    printf("\n===== NOTA FISCAL =====\n");
    printf("Comprador: %s\nCPF: %s\nEmail: %s\nEndereco: %s, %s, %s - %s | CEP: %s\n",
           comprador.nome, comprador.cpf, comprador.email,
           comprador.endereco.rua, comprador.endereco.bairro,
           comprador.endereco.cidade, comprador.endereco.estado,
           comprador.endereco.cep);

    printf("\nProdutos:\n");
    for (int i = 0; i < venda.qtd_itens; i++) {
        printf("- %s | Qtde: %d | Unit: R$%.2f | Total: R$%.2f\n",
               venda.itens[i].nome_produto, venda.itens[i].quantidade,
               venda.itens[i].preco_unitario, venda.itens[i].preco_total);
    }

    float frete = calcularFrete(venda.total_venda);
    printf("\nTotal da Venda: R$%.2f\nFrete: R$%.2f\nTotal Geral: R$%.2f\n",
           venda.total_venda, frete, venda.total_venda + frete);
    printf("==========================\n");
}

void preencherDadosNotaFiscal() {
    Comprador c;
    Venda v;
    v.total_venda = 0.0f;

    printf("=== Cadastro do Comprador ===\n");
    printf("Nome: ");
    scanf(" %[^\n]", c.nome);
    printf("CPF: ");
    scanf(" %[^\n]", c.cpf);
    printf("Email: ");
    scanf(" %[^\n]", c.email);
    printf("Rua: ");
    scanf(" %[^\n]", c.endereco.rua);
    printf("Bairro: ");
    scanf(" %[^\n]", c.endereco.bairro);
    printf("Cidade: ");
    scanf(" %[^\n]", c.endereco.cidade);
    printf("Estado (UF): ");
    scanf(" %[^\n]", c.endereco.estado);
    printf("CEP: ");
    scanf(" %[^\n]", c.endereco.cep);

    printf("\n=== Cadastro da Venda ===\n");
    printf("Codigo da venda: ");
    scanf("%d", &v.codigo);

    printf("Quantidade de itens: ");
    scanf("%d", &v.qtd_itens);

    for (int i = 0; i < v.qtd_itens; i++) {
        printf("\n--- Produto %d ---\n", i + 1);
        printf("Nome do produto: ");
        scanf(" %[^\n]", v.itens[i].nome_produto);
        printf("Codigo do produto: ");
        scanf("%d", &v.itens[i].codigo_produto);
        printf("Quantidade vendida: ");
        scanf("%d", &v.itens[i].quantidade);
        printf("Preco unitario: ");
        scanf("%f", &v.itens[i].preco_unitario);

        v.itens[i].preco_total = v.itens[i].quantidade * v.itens[i].preco_unitario;
        v.total_venda += v.itens[i].preco_total;
    }

    emitirNotaFiscal(v, c);
}

int main() {
    preencherDadosNotaFiscal();
    return 0;
}
