// Modulo: Emissao da Nota Fiscal
// Responsavel: Arthur Henrique Gomes

#include <stdio.h>
#include <string.h>

#define MAX_ITENS 50

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
    ItemVenda itens[MAX_ITENS];
    int qtd_itens;
    float total_venda;
} Venda;

// Estrutura para Vendedor
typedef struct {
    char nome[100];
    char cnpj[20];
    char email[100];
} Vendedor;

typedef struct {
    char nome_produto[100];
    int codigo_produto;
    float preco_unitario;
} Produto;

// Arrays para armazenar cadastros
Produto produtos[MAX_ITENS];
int qtd_produtos = 0;
Vendedor vendedores[MAX_ITENS];
int qtd_vendedores = 0;
Comprador compradores[MAX_ITENS];
int qtd_compradores = 0;
Venda vendas[MAX_ITENS];
int qtd_vendas = 0;

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

    printf("\nProdutos Vendidos:\n");
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

// Funções de cadastro
void cadastrarProduto() {
    if (qtd_produtos >= MAX_ITENS) {
        printf("Limite de produtos atingido!\n");
        return;
    }
    Produto *p = &produtos[qtd_produtos++];
    printf("Nome do produto: ");
scanf(" %[^\n]", p->nome_produto);
    printf("Codigo do produto: ");
    scanf("%d", &p->codigo_produto);
    printf("Preco unitario: ");
    scanf("%f", &p->preco_unitario);
}

void cadastrarVendedor() {
    if (qtd_vendedores >= MAX_ITENS) {
        printf("Limite de vendedores atingido!\n");
        return;
    }
    Vendedor *v = &vendedores[qtd_vendedores++];
    printf("Nome do vendedor: ");
scanf(" %[^\n]", v->nome);
printf("CNPJ: ");
scanf(" %[^\n]", v->cnpj);
printf("Email: ");
scanf(" %[^\n]", v->email);
}

void cadastrarComprador() {
    if (qtd_compradores >= MAX_ITENS) {
        printf("Limite de compradores atingido!\n");
        return;
    }
    Comprador *c = &compradores[qtd_compradores++];
    printf("Nome: ");
scanf(" %[^\n]", c->nome);
    printf("CPF: ");
scanf(" %[^\n]", c->cpf);
printf("Email: ");
scanf(" %[^\n]", c->email);
printf("Rua: ");
scanf(" %[^\n]", c->endereco.rua);
printf("Bairro: ");
scanf(" %[^\n]", c->endereco.bairro);
printf("Cidade: ");
scanf(" %[^\n]", c->endereco.cidade);
printf("Estado (UF): ");
scanf(" %[^\n]", c->endereco.estado);
printf("CEP: ");
scanf(" %[^\n]", c->endereco.cep);
}

void cadastrarVenda() {
    if (qtd_vendas >= MAX_ITENS) {
        printf("Limite de vendas atingido!\n");
        return;
    }
    Venda *v = &vendas[qtd_vendas++];
    v->total_venda = 0.0f;
    printf("Codigo da venda: ");
    scanf("%d", &v->codigo);
    printf("Quantidade de itens: ");
    scanf("%d", &v->qtd_itens);
    for (int i = 0; i < v->qtd_itens; i++) {
        printf("\n--- Produto %d ---\n", i + 1);
printf("Nome do produto: ");
scanf(" %[^\n]", v->itens[i].nome_produto);
printf("Codigo do produto: ");
        scanf("%d", &v->itens[i].codigo_produto);
        printf("Quantidade vendida: ");
        scanf("%d", &v->itens[i].quantidade);
        printf("Preco unitario: ");
        scanf("%f", &v->itens[i].preco_unitario);
        v->itens[i].preco_total = v->itens[i].quantidade * v->itens[i].preco_unitario;
        v->total_venda += v->itens[i].preco_total;
    }
}

int main() {
    int opcao;
    do {
        printf("\n===== MENU EMISSAO DE NOTA FISCAL =====\n");
        printf("1. Cadastrar produto\n");
        printf("2. Cadastrar vendedor\n");
        printf("3. Cadastrar comprador\n");
        printf("4. Cadastrar venda\n");
        printf("5. Emitir nota fiscal\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                cadastrarProduto();
                break;
            case 2:
                cadastrarVendedor();
                break;
            case 3:
                cadastrarComprador();
                break;
            case 4:
                cadastrarVenda();
                break;
            case 5:
                if (qtd_vendas > 0 && qtd_compradores > 0) {
                    emitirNotaFiscal(vendas[qtd_vendas-1], compradores[qtd_compradores-1]);
                } else {
                    printf("Cadastre pelo menos um comprador e uma venda antes de emitir a nota fiscal!\n");
                }
                break;
            case 0:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);
    return 0;
}
