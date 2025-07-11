
// Modulo: Cadastro de Vendedores
// Responsavel: Arthur Henrique Gomes


#include <stdio.h>
#include <string.h>

#define MAX_VENDEDORES 100

typedef struct {
    int numero;
    char nome[100];
    float salario_fixo;
    float comissao_total;
} Vendedor;


void limparEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int inserirVendedor(Vendedor vendedores[], int *n) {
    if (*n >= MAX_VENDEDORES) return 0;

    Vendedor novo;

    printf("\nNumero do vendedor: ");
    scanf("%d", &novo.numero);
    limparEntrada(); 

   
    for (int i = 0; i < *n; i++) {
        if (vendedores[i].numero == novo.numero) {
            printf("\nErro: Vendedor com este numero ja existe.\n");
            return 0;
        }
    }

    printf("Nome do vendedor: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = 0; 

    printf("Salario fixo: R$ ");
    scanf("%f", &novo.salario_fixo);
    limparEntrada(); 

    novo.comissao_total = 0;

    vendedores[*n] = novo;
    (*n)++;
    return 1;
}

int consultarVendedor(Vendedor vendedores[], int n, int numero) {
    for (int i = 0; i < n; i++) {
        if (vendedores[i].numero == numero) {
            printf("\nVendedor encontrado:\nNome: %s\nNumero: %d\nSalario Fixo: R$%.2f\nComissao Total: R$%.2f\n",
                   vendedores[i].nome, vendedores[i].numero,
                   vendedores[i].salario_fixo, vendedores[i].comissao_total);
            return i;
        }
    }
    printf("\nVendedor nao encontrado.\n");
    return -1;
}

int alterarVendedor(Vendedor vendedores[], int n, int numero) {
    int idx = consultarVendedor(vendedores, n, numero);
    if (idx == -1) return 0;

    printf("\nNovo nome: ");
    limparEntrada(); 
    fgets(vendedores[idx].nome, sizeof(vendedores[idx].nome), stdin);
    vendedores[idx].nome[strcspn(vendedores[idx].nome, "\n")] = 0;

    printf("Novo salario fixo: R$ ");
    scanf("%f", &vendedores[idx].salario_fixo);
    limparEntrada(); 

    return 1;
}

int excluirVendedor(Vendedor vendedores[], int *n, int numero) {
    for (int i = 0; i < *n; i++) {
        if (vendedores[i].numero == numero) {
            for (int j = i; j < *n - 1; j++) {
                vendedores[j] = vendedores[j + 1];
            }
            (*n)--;
            return 1;
        }
    }
    return 0;
}

void atualizarComissao(Vendedor *v, float valor_venda) {
    v->comissao_total += valor_venda * 0.03f;
}

void listarVendedores(Vendedor vendedores[], int n) {
    printf("\nLista de Vendedores:\n");
    for (int i = 0; i < n; i++) {
        printf("%d - %s | Salario: R$%.2f | Comissao: R$%.2f\n",
               vendedores[i].numero, vendedores[i].nome,
               vendedores[i].salario_fixo, vendedores[i].comissao_total);
    }
}
int main() {
    Vendedor vendedores[MAX_VENDEDORES];
    int n = 0;
    int opcao, numero;

    do {
        printf("\nMenu:\n");
        printf("1. Inserir Vendedor\n");
        printf("2. Consultar Vendedor\n");
        printf("3. Alterar Vendedor\n");
        printf("4. Excluir Vendedor\n");
        printf("5. Listar Vendedores\n");
        printf("6. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparEntrada(); 

        switch (opcao) {
            case 1:
                if (inserirVendedor(vendedores, &n)) {
                    printf("\nVendedor inserido com sucesso.\n");
                } else {
                    printf("\nErro ao inserir vendedor.\n");
                }
                break;
            case 2:
                printf("\nNumero do vendedor: ");
                scanf("%d", &numero);
                consultarVendedor(vendedores, n, numero);
                break;
            case 3:
                printf("\nNumero do vendedor: ");
                scanf("%d", &numero);
                if (alterarVendedor(vendedores, n, numero)) {
                    printf("\nVendedor alterado com sucesso.\n");
                } else {
                    printf("\nErro ao alterar vendedor.\n");
                }
                break;
            case 4:
                printf("\nNumero do vendedor: ");
                scanf("%d", &numero);
                if (excluirVendedor(vendedores, &n, numero)) {
                    printf("\nVendedor excluido com sucesso.\n");
                } else {
                    printf("\nErro ao excluir vendedor.\n");
                }
                break;
            case 5:
                listarVendedores(vendedores, n);
                break;
            case 6:
                printf("\nSaindo...\n");
                break;
            default:
                printf("\nOpcao invalida. Tente novamente.\n");
        }
    } while (opcao != 6);

    return 0;
