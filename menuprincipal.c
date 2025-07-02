#include <stdio.h>
#include <string.h>

#define MAX_PRODUTOS 100
#define MAX_VENDEDORES 100
#define MAX_COMPRADORES 100
#define MAX_ITENS_VENDA 20
#define MAX_VENDAS 100

typedef struct {
    char nome[100];
    int codigo;
    int estoque;
    float preco;
} Produto;

typedef struct {
    char nome[100];
    int numero;
    float salario_fixo;
    float comissao_total;
} Vendedor;

typedef struct {
    char rua[100];
    char bairro[100];
    char cidade[100];
    char estado[100];
    char cep[20];
} Endereco;

typedef struct {
    char nome[100];
    char cpf[15];
    char email[100];
    Endereco endereco;
} Comprador;

typedef struct {
    int codigo_produto;
    char nome_produto[100];
    int quantidade;
    float preco_unitario;
    float preco_total;
} ItemVenda;

typedef struct {
    int codigo;
    int vendedor_numero;
    char comprador_cpf[15];
    int qtd_itens;
    ItemVenda itens[MAX_ITENS_VENDA];
    float total_venda;
} Venda;

int total_produtos = 0;
Produto produtos[MAX_PRODUTOS];

int total_vendedores = 0;
Vendedor vendedores[MAX_VENDEDORES];

int total_compradores = 0;
Comprador compradores[MAX_COMPRADORES];

int total_vendas = 0;
Venda vendas[MAX_VENDAS];

int buscarProduto(int codigo) {
    for (int i = 0; i < total_produtos; i++)
        if (produtos[i].codigo == codigo)
            return i;
    return -1;
}

int buscarProdutoPorNome(char* nome) {
    for (int i = 0; i < total_produtos; i++)
        if (strcmp(produtos[i].nome, nome) == 0)
            return i;
    return -1;
}

int buscarVendedor(int numero) {
    for (int i = 0; i < total_vendedores; i++)
        if (vendedores[i].numero == numero)
            return i;
    return -1;
}

int buscarVendedorPorNome(char* nome) {
    for (int i = 0; i < total_vendedores; i++)
        if (strcmp(vendedores[i].nome, nome) == 0)
            return i;
    return -1;
}

int buscarComprador(char* cpf) {
    for (int i = 0; i < total_compradores; i++)
        if (strcmp(compradores[i].cpf, cpf) == 0)
            return i;
    return -1;
}

int buscarCompradorPorNome(char* nome) {
    for (int i = 0; i < total_compradores; i++)
        if (strcmp(compradores[i].nome, nome) == 0)
            return i;
    return -1;
}

int buscarVenda(int codigo) {
    for (int i = 0; i < total_vendas; i++)
        if (vendas[i].codigo == codigo)
            return i;
    return -1;
}

float calcularFrete(float total) {
    if (total <= 100.0f) return 30.0f;
    if (total <= 300.0f) return 20.0f;
    return 0.0f;
}

// =================== MENUS DE CADASTRO ===================

void menuCadastroProdutos() {
    int opcao;
    do {
        printf("\n--- Menu Produtos ---\n");
        printf("1. Inserir\n2. Consultar\n3. Alterar\n4. Excluir\n5. Listar Todos\n0. Voltar\nOpcao: ");
        scanf("%d", &opcao);
        if (opcao == 1 && total_produtos < MAX_PRODUTOS) {
            Produto p;
            printf("\n=== Cadastro de Produto ===\n");
            printf("Nome: "); scanf(" %[^\n]", p.nome);
            printf("Codigo: "); scanf("%d", &p.codigo);
            if (buscarProduto(p.codigo) != -1) { printf("Codigo ja cadastrado.\n"); continue; }
            printf("Qtd em estoque: "); scanf("%d", &p.estoque);
            printf("Preco (R$): "); scanf("%f", &p.preco);
            produtos[total_produtos++] = p;
            printf("Produto cadastrado.\n");
        }
        else if (opcao == 2) {
            int subopcao;
            printf("\nConsultar por:\n1. Codigo\n2. Nome\nOpcao: ");
            scanf("%d", &subopcao);
            if (subopcao == 1) {
                int codigo;
                printf("Digite o codigo do produto: ");
                scanf("%d", &codigo);
                int idx = buscarProduto(codigo);
                if (idx == -1) printf("Produto nao encontrado.\n");
                else printf("\nNome: %s\nCodigo: %d\nQtd em estoque: %d\nPreco: R$%.2f\n",
                    produtos[idx].nome, produtos[idx].codigo, produtos[idx].estoque, produtos[idx].preco);
            } else if (subopcao == 2) {
                char nome[100];
                printf("Digite o nome do produto: ");
                scanf(" %[^\n]", nome);
                int idx = buscarProdutoPorNome(nome);
                if (idx == -1) printf("Produto nao encontrado.\n");
                else printf("\nNome: %s\nCodigo: %d\nQtd em estoque: %d\nPreco: R$%.2f\n",
                    produtos[idx].nome, produtos[idx].codigo, produtos[idx].estoque, produtos[idx].preco);
            }
        }
        else if (opcao == 3) {
            int codigo;
            printf("Codigo do produto a alterar: ");
            scanf("%d", &codigo);
            int idx = buscarProduto(codigo);
            if (idx == -1) { printf("Nao encontrado.\n"); continue; }
            printf("Novo nome: "); scanf(" %[^\n]", produtos[idx].nome);
            printf("Nova qtd em estoque: "); scanf("%d", &produtos[idx].estoque);
            printf("Novo preco (R$): "); scanf("%f", &produtos[idx].preco);
        }
        else if (opcao == 4) {
            int codigo;
            printf("Codigo do produto a excluir: ");
            scanf("%d", &codigo);
            int idx = buscarProduto(codigo);
            if (idx == -1) { printf("Nao encontrado.\n"); continue; }
            for (int i = idx; i < total_produtos - 1; i++)
                produtos[i] = produtos[i+1];
            total_produtos--;
            printf("Excluido.\n");
        }
        else if (opcao == 5) {
            printf("\n--- Lista de Todos os Produtos ---\n");
            for (int i = 0; i < total_produtos; i++) {
                printf("Nome: %s | Codigo: %d | Qtd em estoque: %d | Preco: R$%.2f\n",
                    produtos[i].nome, produtos[i].codigo, produtos[i].estoque, produtos[i].preco);
            }
        }
    } while (opcao != 0);
}

void menuCadastroVendedores() {
    int opcao;
    do {
        printf("\n--- Menu Vendedores ---\n");
        printf("1. Inserir\n2. Consultar\n3. Alterar\n4. Excluir\n5. Listar Todos\n0. Voltar\nOpcao: ");
        scanf("%d", &opcao);
        if (opcao == 1 && total_vendedores < MAX_VENDEDORES) {
            Vendedor v;
            printf("\n=== Cadastro de Vendedor ===\n");
            printf("Nome: "); scanf(" %[^\n]", v.nome);
            printf("Numero: "); scanf("%d", &v.numero);
            if (buscarVendedor(v.numero) != -1) { printf("Numero ja cadastrado.\n"); continue; }
            printf("Salario fixo (R$): "); scanf("%f", &v.salario_fixo);
            v.comissao_total = 0.0f;
            vendedores[total_vendedores++] = v;
            printf("Vendedor cadastrado.\n");
        }
        else if (opcao == 2) {
            int subopcao;
            printf("\nConsultar por:\n1. Numero\n2. Nome\nOpcao: ");
            scanf("%d", &subopcao);
            if (subopcao == 1) {
                int numero;
                printf("Digite o numero do vendedor: ");
                scanf("%d", &numero);
                int idx = buscarVendedor(numero);
                if (idx == -1) printf("Vendedor nao encontrado.\n");
                else printf("\nNome: %s\nNumero: %d\nSalario: R$%.2f\nComissao: R$%.2f\n",
                    vendedores[idx].nome, vendedores[idx].numero,
                    vendedores[idx].salario_fixo, vendedores[idx].comissao_total);
            } else if (subopcao == 2) {
                char nome[100];
                printf("Digite o nome do vendedor: ");
                scanf(" %[^\n]", nome);
                int idx = buscarVendedorPorNome(nome);
                if (idx == -1) printf("Vendedor nao encontrado.\n");
                else printf("\nNome: %s\nNumero: %d\nSalario: R$%.2f\nComissao: R$%.2f\n",
                    vendedores[idx].nome, vendedores[idx].numero,
                    vendedores[idx].salario_fixo, vendedores[idx].comissao_total);
            }
        }
        else if (opcao == 3) {
            int numero;
            printf("Numero do vendedor a alterar: ");
            scanf("%d", &numero);
            int idx = buscarVendedor(numero);
            if (idx == -1) { printf("Nao encontrado.\n"); continue; }
            printf("Novo nome: "); scanf(" %[^\n]", vendedores[idx].nome);
            printf("Novo salario fixo (R$): "); scanf("%f", &vendedores[idx].salario_fixo);
        }
        else if (opcao == 4) {
            int numero;
            printf("Numero do vendedor a excluir: ");
            scanf("%d", &numero);
            int idx = buscarVendedor(numero);
            if (idx == -1) { printf("Nao encontrado.\n"); continue; }
            for (int i = idx; i < total_vendedores - 1; i++)
                vendedores[i] = vendedores[i+1];
            total_vendedores--;
            printf("Excluido.\n");
        }
        else if (opcao == 5) {
            printf("\n--- Lista de Todos os Vendedores ---\n");
            for (int i = 0; i < total_vendedores; i++) {
                printf("Nome: %s | Numero: %d | Salario: R$%.2f | Comissao: R$%.2f\n",
                    vendedores[i].nome, vendedores[i].numero,
                    vendedores[i].salario_fixo, vendedores[i].comissao_total);
            }
        }
    } while (opcao != 0);
}

void menuCadastroCompradores() {
    int opcao;
    do {
        printf("\n--- Menu Compradores ---\n");
        printf("1. Inserir\n2. Consultar\n3. Alterar\n4. Excluir\n5. Listar Todos\n0. Voltar\nOpcao: ");
        scanf("%d", &opcao);
        if (opcao == 1 && total_compradores < MAX_COMPRADORES) {
            Comprador c;
            printf("\n=== Cadastro de Comprador ===\n");
            printf("Nome: "); scanf(" %[^\n]", c.nome);
            printf("CPF: "); scanf("%s", c.cpf);
            if (buscarComprador(c.cpf) != -1) { printf("CPF ja cadastrado.\n"); continue; }
            printf("Email: "); scanf(" %[^\n]", c.email);
            printf("Rua: "); scanf(" %[^\n]", c.endereco.rua);
            printf("Bairro: "); scanf(" %[^\n]", c.endereco.bairro);
            printf("Cidade: "); scanf(" %[^\n]", c.endereco.cidade);
            printf("Estado: "); scanf(" %[^\n]", c.endereco.estado);
            printf("CEP: "); scanf(" %[^\n]", c.endereco.cep);
            compradores[total_compradores++] = c;
            printf("Comprador cadastrado.\n");
        }
        else if (opcao == 2) {
            int subopcao;
            printf("\nConsultar por:\n1. CPF\n2. Nome\nOpcao: ");
            scanf("%d", &subopcao);
            if (subopcao == 1) {
                char cpf[15];
                printf("Digite o CPF do comprador: ");
                scanf("%s", cpf);
                int idx = buscarComprador(cpf);
                if (idx == -1) printf("Comprador nao encontrado.\n");
                else printf("\nNome: %s\nCPF: %s\nEmail: %s\nEndereco: %s, %s, %s - %s | CEP: %s\n",
                    compradores[idx].nome, compradores[idx].cpf, compradores[idx].email,
                    compradores[idx].endereco.rua, compradores[idx].endereco.bairro,
                    compradores[idx].endereco.cidade, compradores[idx].endereco.estado,
                    compradores[idx].endereco.cep);
            } else if (subopcao == 2) {
                char nome[100];
                printf("Digite o nome do comprador: ");
                scanf(" %[^\n]", nome);
                int idx = buscarCompradorPorNome(nome);
                if (idx == -1) printf("Comprador nao encontrado.\n");
                else printf("\nNome: %s\nCPF: %s\nEmail: %s\nEndereco: %s, %s, %s - %s | CEP: %s\n",
                    compradores[idx].nome, compradores[idx].cpf, compradores[idx].email,
                    compradores[idx].endereco.rua, compradores[idx].endereco.bairro,
                    compradores[idx].endereco.cidade, compradores[idx].endereco.estado,
                    compradores[idx].endereco.cep);
            }
        }
        else if (opcao == 3) {
            char cpf[15];
            printf("CPF do comprador a alterar: ");
            scanf("%s", cpf);
            int idx = buscarComprador(cpf);
            if (idx == -1) { printf("Nao encontrado.\n"); continue; }
            printf("Novo nome: "); scanf(" %[^\n]", compradores[idx].nome);
            printf("Novo email: "); scanf(" %[^\n]", compradores[idx].email);
            printf("Nova rua: "); scanf(" %[^\n]", compradores[idx].endereco.rua);
            printf("Novo bairro: "); scanf(" %[^\n]", compradores[idx].endereco.bairro);
            printf("Nova cidade: "); scanf(" %[^\n]", compradores[idx].endereco.cidade);
            printf("Novo estado: "); scanf(" %[^\n]", compradores[idx].endereco.estado);
            printf("Novo CEP: "); scanf(" %[^\n]", compradores[idx].endereco.cep);
        }
        else if (opcao == 4) {
            char cpf[15];
            printf("CPF do comprador a excluir: ");
            scanf("%s", cpf);
            int idx = buscarComprador(cpf);
            if (idx == -1) { printf("Nao encontrado.\n"); continue; }
            for (int i = idx; i < total_compradores - 1; i++)
                compradores[i] = compradores[i+1];
            total_compradores--;
            printf("Excluido.\n");
        }
        else if (opcao == 5) {
            printf("\n--- Lista de Todos os Compradores ---\n");
            for (int i = 0; i < total_compradores; i++) {
                printf("Nome: %s | CPF: %s | Email: %s | Endereco: %s, %s, %s - %s | CEP: %s\n",
                    compradores[i].nome, compradores[i].cpf, compradores[i].email,
                    compradores[i].endereco.rua, compradores[i].endereco.bairro,
                    compradores[i].endereco.cidade, compradores[i].endereco.estado,
                    compradores[i].endereco.cep);
            }
        }
    } while (opcao != 0);
}

void menuCadastroVendas() {
    int opcao;
    do {
        printf("\n--- Menu Vendas ---\n");
        printf("1. Inserir\n2. Consultar\n3. Alterar\n4. Excluir\n5. Listar Todas\n0. Voltar\nOpcao: ");
        scanf("%d", &opcao);
        if (opcao == 1 && total_vendas < MAX_VENDAS) {
            Venda v;
            printf("\n=== Cadastro de Venda ===\n");
            printf("Codigo da venda: "); scanf("%d", &v.codigo);
            printf("Numero do vendedor: "); scanf("%d", &v.vendedor_numero);
            if (buscarVendedor(v.vendedor_numero) == -1) { printf("Vendedor nao encontrado.\n"); continue; }
            printf("CPF do comprador: "); scanf("%s", v.comprador_cpf);
            if (buscarComprador(v.comprador_cpf) == -1) { printf("Comprador nao encontrado.\n"); continue; }
            printf("Qtd de itens: "); scanf("%d", &v.qtd_itens);
            v.total_venda = 0.0f;
            for (int i = 0; i < v.qtd_itens; i++) {
                printf("--- Produto %d ---\n", i + 1);
                printf("Codigo do produto: "); scanf("%d", &v.itens[i].codigo_produto);
                int idx = buscarProduto(v.itens[i].codigo_produto);
                if (idx == -1) { printf("Produto nao encontrado.\n"); i--; continue; }
                printf("Qtd vendida: "); scanf("%d", &v.itens[i].quantidade);
                if (produtos[idx].estoque < v.itens[i].quantidade) {
                    printf("Estoque insuficiente.\n"); i--; continue;
                }
                produtos[idx].estoque -= v.itens[i].quantidade;
                strcpy(v.itens[i].nome_produto, produtos[idx].nome);
                v.itens[i].preco_unitario = produtos[idx].preco;
                v.itens[i].preco_total = v.itens[i].quantidade * v.itens[i].preco_unitario;
                v.total_venda += v.itens[i].preco_total;
            }
            int idx_vend = buscarVendedor(v.vendedor_numero);
            if (idx_vend != -1)
                vendedores[idx_vend].comissao_total += v.total_venda * 0.03f;
            vendas[total_vendas++] = v;
            printf("Venda cadastrada.\n");
        }
        else if (opcao == 2) {
            int subopcao;
            printf("\nConsultar por:\n1. Codigo da venda\n2. CPF do comprador\nOpcao: ");
            scanf("%d", &subopcao);
            if (subopcao == 1) {
                int codigo;
                printf("Digite o codigo da venda: ");
                scanf("%d", &codigo);
                int idx = buscarVenda(codigo);
                if (idx == -1) printf("Venda nao encontrada.\n");
                else {
                    Venda *v = &vendas[idx];
                    printf("\nCodigo: %d\nVendedor: %d\nComprador: %s\nQtd de itens: %d\nTotal: R$%.2f\n",
                        v->codigo, v->vendedor_numero, v->comprador_cpf, v->qtd_itens, v->total_venda);
                }
            } else if (subopcao == 2) {
                char cpf[15];
                printf("Digite o CPF do comprador: ");
                scanf("%s", cpf);
                int encontrou = 0;
                for (int i = 0; i < total_vendas; i++) {
                    if (strcmp(vendas[i].comprador_cpf, cpf) == 0) {
                        printf("\nCodigo: %d\nVendedor: %d\nComprador: %s\nQtd de itens: %d\nTotal: R$%.2f\n",
                            vendas[i].codigo, vendas[i].vendedor_numero, vendas[i].comprador_cpf, vendas[i].qtd_itens, vendas[i].total_venda);
                        encontrou = 1;
                    }
                }
                if (!encontrou) printf("Nenhuma venda encontrada para esse CPF.\n");
            }
        }
        else if (opcao == 5) {
            printf("\n--- Lista de Todas as Vendas ---\n");
            for (int i = 0; i < total_vendas; i++) {
                printf("Codigo: %d | Vendedor: %d | Comprador: %s | Qtd de itens: %d | Total: R$%.2f\n",
                    vendas[i].codigo, vendas[i].vendedor_numero, vendas[i].comprador_cpf, vendas[i].qtd_itens, vendas[i].total_venda);
            }
        }
    } while (opcao != 0);
}

void menuNotaFiscal() {
    int codigo;
    printf("\n=== Emissao de Nota Fiscal ===\n");
    printf("Codigo da venda para emitir nota: ");
    scanf("%d", &codigo);
    int idx = buscarVenda(codigo);
    if (idx == -1) { printf("Venda nao encontrada.\n"); return; }
    Venda *v = &vendas[idx];
    int idx_comp = buscarComprador(v->comprador_cpf);
    if (idx_comp == -1) { printf("Comprador nao encontrado.\n"); return; }
    Comprador *c = &compradores[idx_comp];
    printf("\n===== NOTA FISCAL =====\n");
    printf("Comprador: %s\nCPF: %s\nEmail: %s\nEndereco: %s, %s, %s - %s | CEP: %s\n",
        c->nome, c->cpf, c->email, c->endereco.rua, c->endereco.bairro,
        c->endereco.cidade, c->endereco.estado, c->endereco.cep);
    printf("\nProdutos Vendidos:\n");
    for (int i = 0; i < v->qtd_itens; i++) {
        printf("- %s | Qtd: %d | Unit: R$%.2f | Total: R$%.2f\n",
            v->itens[i].nome_produto, v->itens[i].quantidade,
            v->itens[i].preco_unitario, v->itens[i].preco_total);
    }
    float frete = calcularFrete(v->total_venda);
    printf("\nTotal da Venda: R$%.2f\nFrete: R$%.2f\nTotal Geral: R$%.2f\n",
        v->total_venda, frete, v->total_venda + frete);
    printf("==========================\n");
}

int main() {
    int opcao;
    do {
        printf("\n===== MENU PRINCIPAL =====\n");
        printf("1. Produtos\n2. Vendedores\n3. Compradores\n4. Vendas\n5. Nota Fiscal\n0. Sair\nOpcao: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1: menuCadastroProdutos(); break;
            case 2: menuCadastroVendedores(); break;
            case 3: menuCadastroCompradores(); break;
            case 4: menuCadastroVendas(); break;
            case 5: menuNotaFiscal(); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
    return 0;
}