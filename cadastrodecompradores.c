// Modulo: Cadastro de Compradores
// Responsavel: Henrique Fernandes Silva

#include <stdio.h>
#include <string.h>

#define MAX_COMPRADORES 100

typedef struct {
    char rua[100];
    char bairro[50];
    char cidade[50];
    char estado[3];
    char cep[10];
} Endereco;


typedef struct {
    char nome[100];
    char cpf[15];
    char email[100];
    Endereco endereco;
} Comprador;

Comprador compradores[MAX_COMPRADORES];
int total_compradores = 0;

int buscarCompradorPorCPF(const char* cpf) {
    for (int i = 0; i < total_compradores; i++) {
        if (strcmp(compradores[i].cpf, cpf) == 0) {
            return i;
        }
    }
    return -1;
}

void inserirComprador() {
    if (total_compradores >= MAX_COMPRADORES) {
        printf("Limite de compradores atingido.\n");
        return;
    }

    Comprador novo;

printf("Nome: ");
scanf(" %[^\n]", novo.nome);
printf("CPF: ");
scanf(" %[^\n]", novo.cpf);
printf("Email: ");
scanf(" %[^\n]", novo.email);
printf("Rua: ");
scanf(" %[^\n]", novo.endereco.rua);
printf("Bairro: ");
scanf(" %[^\n]", novo.endereco.bairro);
printf("Cidade: ");
scanf(" %[^\n]", novo.endereco.cidade);
printf("Estado (UF): ");
scanf(" %[^\n]", novo.endereco.estado);
printf("CEP: ");
scanf(" %[^\n]", novo.endereco.cep);

    if (buscarCompradorPorCPF(novo.cpf) != -1) {
        printf("CPF ja cadastrado.\n");
        return;
    }

    compradores[total_compradores++] = novo;
    printf("Comprador cadastrado com sucesso.\n");
}

void consultarComprador() {
    char cpf[15];
    printf("Digite o CPF do comprador: ");
    scanf(" %[^\n]", cpf);

    int idx = buscarCompradorPorCPF(cpf);
    if (idx != -1) {
        Comprador c = compradores[idx];
        printf("\nNome: %s\nCPF: %s\nEmail: %s\nEndereco: %s, %s, %s - %s | CEP: %s\n",
               c.nome, c.cpf, c.email,
               c.endereco.rua, c.endereco.bairro, c.endereco.cidade,
               c.endereco.estado, c.endereco.cep);
    } else {
        printf("Comprador nao encontrado.\n");
    }
}

void alterarComprador() {
    char cpf[15];
    printf("Digite o CPF do comprador a alterar: ");
scanf(" %[^\n]", cpf);

    int idx = buscarCompradorPorCPF(cpf);
    if (idx != -1) {
        printf("Digite os novos dados:\n");
        printf("Nome: ");
char cpf[15];
printf("Digite o CPF do comprador a alterar: ");
scanf(" %[^\n]", cpf);
        printf("Rua: ");
        scanf(" %[^\n]", compradores[idx].endereco.rua);
printf("Digite os novos dados:\n");
printf("Nome: ");
scanf(" %[^\n]", compradores[idx].nome);
printf("Email: ");
scanf(" %[^\n]", compradores[idx].email);
printf("Rua: ");
scanf(" %[^\n]", compradores[idx].endereco.rua);
printf("Bairro: ");
scanf(" %[^\n]", compradores[idx].endereco.bairro);
printf("Cidade: ");
scanf(" %[^\n]", compradores[idx].endereco.cidade);
printf("Estado: ");
scanf(" %[^\n]", compradores[idx].endereco.estado);
printf("CEP: ");
scanf(" %[^\n]", compradores[idx].endereco.cep);
printf("Dados atualizados com sucesso.\n");
    }
}

void excluirComprador() {
    char cpf[15];
    printf("Digite o CPF do comprador a excluir: ");
    scanf(" %[^\n]", cpf);

    int idx = buscarCompradorPorCPF(cpf);
    if (idx != -1) {
        for (int i = idx; i < total_compradores - 1; i++) {
            compradores[i] = compradores[i + 1];
        }
        total_compradores--;
        printf("Comprador excluido com sucesso.\n");
    } else {
        printf("Comprador nao encontrado.\n");
    }
}

void listarCompradores() {
    if (total_compradores == 0) {
        printf("Nenhum comprador cadastrado.\n");
        return;
    }
    printf("\nLista de Compradores:\n");
    for (int i = 0; i < total_compradores; i++) {
        Comprador c = compradores[i];
        printf("%d. Nome: %s | CPF: %s | Email: %s | Endereco: %s, %s, %s - %s | CEP: %s\n",
               i + 1, c.nome, c.cpf, c.email,
               c.endereco.rua, c.endereco.bairro, c.endereco.cidade,
               c.endereco.estado, c.endereco.cep);
    }
}

void menuCadastroCompradores() {
    int opcao;
    do {
        printf("\n===== MENU CADASTRO DE COMPRADORES =====\n");
        printf("1. Inserir comprador\n");
        printf("2. Consultar comprador\n");
        printf("3. Alterar comprador\n");
        printf("4. Excluir comprador\n");
        printf("5. Listar todos os compradores\n");
        printf("0. Voltar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: inserirComprador(); break;
            case 2: consultarComprador(); break;
            case 3: alterarComprador(); break;
            case 4: excluirComprador(); break;
            case 5: listarCompradores(); break;
            case 0: printf("Voltando...\n"); break;
            default: printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
}

int main() {
    menuCadastroCompradores();
    return 0;
}
