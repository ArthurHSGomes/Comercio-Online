// Modulo: Cadastro de Vendas
// Responsavel: Davi

#include <stdio.h>
#include <string.h>

#define MAX_VENDAS 100
#define MAX_ITENS 50
#define MAX_PRODUTOS 100


typedef struct {
    char nome[100];
    int codigo;
    int quantidade_estoque;
    float preco_venda;
} Produto;


typedef struct {
    char nome_produto[100];
    int codigo_produto;
    int quantidade;
    float preco_unitario;
    float preco_total;
} ItemVenda;


typedef struct {
    int codigo;
    ItemVenda itens[MAX_ITENS];
    int qtd_itens;
    float total_venda;
} Venda;

Produto estoque[MAX_PRODUTOS];
int total_produtos = 0;

Venda vendas[MAX_VENDAS];
int total_vendas = 0;

Produto* buscarProduto(int codigo) {
    for (int i = 0; i < total_produtos; i++) {
        if (estoque[i].codigo == codigo) {
            return &estoque[i];
        }
    }
    return NULL;
}

void inserirVenda() {
    if (total_vendas >= MAX_VENDAS) {
        printf("Limite de vendas atingido.\n");
        return;
    }

    Venda nova;
    nova.total_venda = 0.0f;

    printf("Codigo da venda: ");
    scanf("%d", &nova.codigo);

    printf("Quantidade de itens na venda: ");
    scanf("%d", &nova.qtd_itens);

    for (int i = 0; i < nova.qtd_itens; i++) {
        printf("\n--- Produto %d ---\n", i + 1);
        printf("Codigo do produto: ");
        scanf("%d", &nova.itens[i].codigo_produto);

        Produto* prod = buscarProduto(nova.itens[i].codigo_produto);
        if (prod == NULL) {
            printf("Produto nao encontrado. Venda cancelada.\n");
            return;
        }

        printf("Quantidade desejada: ");
        scanf("%d", &nova.itens[i].quantidade);

        if (nova.itens[i].quantidade > prod->quantidade_estoque) {
            printf("Estoque insuficiente. Venda cancelada.\n");
            return;
        }

        strcpy(nova.itens[i].nome_produto, prod->nome);
        nova.itens[i].preco_unitario = prod->preco_venda;
        nova.itens[i].preco_total = nova.itens[i].quantidade * prod->preco_venda;
        nova.total_venda += nova.itens[i].preco_total;

        prod->quantidade_estoque -= nova.itens[i].quantidade;
    }

    vendas[total_vendas++] = nova;
    printf("Venda cadastrada com sucesso! Total: R$%.2f\n", nova.total_venda);
}

void consultarVenda() {
    int codigo;
    printf("Digite o codigo da venda: ");
    scanf("%d", &codigo);

    for (int i = 0; i < total_vendas; i++) {
        if (vendas[i].codigo == codigo) {
            printf("\nVenda %d - Total: R$%.2f\n", vendas[i].codigo, vendas[i].total_venda);
            for (int j = 0; j < vendas[i].qtd_itens; j++) {
                ItemVenda item = vendas[i].itens[j];
                printf("- %s | Codigo: %d | Qtde: %d | Unit: R$%.2f | Total: R$%.2f\n",
                       item.nome_produto, item.codigo_produto, item.quantidade,
                       item.preco_unitario, item.preco_total);
            }
            return;
        }
    }
    printf("Venda nao encontrada.\n");
}

void alterarVenda() {
    int codigo;
    printf("Informe o codigo da venda a alterar: ");
    scanf("%d", &codigo);

    for (int i = 0; i < total_vendas; i++) {
        if (vendas[i].codigo == codigo) {
            printf("Venda encontrada. Para alterar, cadastre novamente os dados:\n");

            for (int j = 0; j < vendas[i].qtd_itens; j++) {
                Produto* prod = buscarProduto(vendas[i].itens[j].codigo_produto);
                if (prod != NULL) {
                    prod->quantidade_estoque += vendas[i].itens[j].quantidade;
                }
            }

            total_vendas--;
            for (int k = i; k < total_vendas; k++) {
                vendas[k] = vendas[k + 1];
            }

            inserirVenda();
            return;
        }
    }
    printf("Venda nao encontrada.\n");
}

void excluirVenda() {
    int codigo;
    printf("Informe o codigo da venda a excluir: ");
    scanf("%d", &codigo);

    for (int i = 0; i < total_vendas; i++) {
        if (vendas[i].codigo == codigo) {
            for (int j = 0; j < vendas[i].qtd_itens; j++) {
                Produto* prod = buscarProduto(vendas[i].itens[j].codigo_produto);
                if (prod != NULL) {
                    prod->quantidade_estoque += vendas[i].itens[j].quantidade;
                }
            }
            for (int k = i; k < total_vendas - 1; k++) {
                vendas[k] = vendas[k + 1];
            }
            total_vendas--;
            printf("Venda excluida com sucesso.\n");
            return;
        }
    }
    printf("Venda nao encontrada.\n");
}

void listarVendas() {
    printf("\n===== LISTA DE VENDAS =====\n");
    for (int i = 0; i < total_vendas; i++) {
        printf("\nVenda Codigo: %d | Total: R$%.2f\n", vendas[i].codigo, vendas[i].total_venda);
        for (int j = 0; j < vendas[i].qtd_itens; j++) {
            ItemVenda item = vendas[i].itens[j];
            printf("- %s | Qtde: %d | Unit: R$%.2f | Total: R$%.2f\n",
                   item.nome_produto, item.quantidade, item.preco_unitario, item.preco_total);
        }
    }
}

void menuCadastroVendas() {
    int opcao;
    do {
        printf("\n===== MENU CADASTRO DE VENDAS =====\n");
        printf("1. Inserir venda\n");
        printf("2. Consultar venda\n");
        printf("3. Alterar venda\n");
        printf("4. Excluir venda\n");
        printf("5. Listar vendas\n");
        printf("0. Voltar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: inserirVenda(); break;
            case 2: consultarVenda(); break;
            case 3: alterarVenda(); break;
            case 4: excluirVenda(); break;
            case 5: listarVendas(); break;
            case 0: printf("Voltando...\n"); break;
            default: printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
}

int main() {
   
    strcpy(estoque[0].nome, "Teclado USB");
    estoque[0].codigo = 101;
    estoque[0].quantidade_estoque = 10;
    estoque[0].preco_venda = 120.0f;

    strcpy(estoque[1].nome, "Mouse Sem Fio");
    estoque[1].codigo = 102;
    estoque[1].quantidade_estoque = 15;
    estoque[1].preco_venda = 80.0f;

    total_produtos = 2;

    menuCadastroVendas();
    return 0;
}
