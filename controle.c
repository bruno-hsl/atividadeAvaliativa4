#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Veiculo {
    char proprietario[50];
    char combustivel[10];
    char modelo[30];
    char cor[20];
    char chassi[20];
    int ano;
    char placa[8];
    struct Veiculo* prox;
} Veiculo;

Veiculo* inicializarLista() {
    return NULL;
}

Veiculo* criarVeiculo() {
    Veiculo* novoVeiculo = (Veiculo*)malloc(sizeof(Veiculo));
    if (novoVeiculo == NULL) {
        printf("Erro de alocacao de memoria.\n");
        exit(EXIT_FAILURE);
    }
    novoVeiculo->prox = NULL;
    return novoVeiculo;
}

void adicionarVeiculo(Veiculo** lista) {
    Veiculo* novoVeiculo = criarVeiculo();

    printf("Digite o nome do proprietario: ");
    scanf("%s", novoVeiculo->proprietario);

    printf("Digite o tipo de combustivel (alcool, diesel, gasolina): ");
    scanf("%s", novoVeiculo->combustivel);

    printf("Digite o modelo do veiculo: ");
    scanf("%s", novoVeiculo->modelo);

    printf("Digite a cor do veiculo: ");
    scanf("%s", novoVeiculo->cor);

    printf("Digite o numero do chassi: ");
    scanf("%s", novoVeiculo->chassi);

    printf("Digite o ano do veiculo: ");
    scanf("%d", &novoVeiculo->ano);

    printf("Digite a placa do veiculo (3 letras seguidas de 4 numeros): ");
    scanf("%s", novoVeiculo->placa);

    novoVeiculo->prox = *lista;
    *lista = novoVeiculo;
}

void Diesel2010(Veiculo* lista) {
    printf("\nProprietarios com carros a diesel do ano 2010 ou posterior:\n");

    while (lista != NULL) {
        if (strcmp(lista->combustivel, "diesel") == 0 && lista->ano >= 2010) {
            printf("Proprietario: %s\n", lista->proprietario);
        }
        lista = lista->prox;
    }
}

void PlacasJ(Veiculo* lista) {
    printf("\nProprietarios:\n");

    while (lista != NULL) {
        if (lista->placa[0] == 'J' && (lista->placa[7] == '0' || lista->placa[7] == '2' || lista->placa[7] == '4' || lista->placa[7] == '7')) {
            printf("Placa: %s, Proprietario: %s\n", lista->placa, lista->proprietario);
        }
        lista = lista->prox;
    }
}

void verificarVogalSoma(Veiculo* lista) {
    printf("\nModelo e cor dos veiculos com placas que possuem como segunda letra uma vogal e a soma dos valores numericos fornece um numero par:\n");

    while (lista != NULL) {
        char segundaLetraPlaca = lista->placa[1];
        int somaNumerosPlaca = 0;

        for (int i = 3; i <= 6; ++i) {
            somaNumerosPlaca += lista->placa[i] - '0';
        }

        if ((segundaLetraPlaca == 'A' || segundaLetraPlaca == 'E' || segundaLetraPlaca == 'I' ||
             segundaLetraPlaca == 'O' || segundaLetraPlaca == 'U') &&
            somaNumerosPlaca % 2 == 0) {
            printf("Modelo: %s, Cor: %s\n", lista->modelo, lista->cor);
        }
        lista = lista->prox;
    }
}

void trocarProprietario(Veiculo** lista) {
    char chassiTroca[20];
    printf("\nDigite o chassi para troca de proprietario: ");
    scanf("%s", chassiTroca);

    char novoProprietario[50];
    printf("Digite o novo proprietario: ");
    scanf("%s", novoProprietario);

    Veiculo* atual = *lista;

    while (atual != NULL) {
        if (strcmp(atual->chassi, chassiTroca) == 0 && strpbrk(atual->placa, "0") == NULL) {
            strncpy(atual->proprietario, novoProprietario, sizeof(atual->proprietario));
            printf("Proprietario alterado com sucesso.\n");
            return;
        }
        atual = atual->prox;
    }

    printf("Nenhum carro encontrado com o chassi fornecido ou a placa possui digito zero.\n");
}

void liberarVeiculos(Veiculo* lista) {
    Veiculo* atual = lista;
    Veiculo* proximoVeiculo;

    while (atual != NULL) {
        proximoVeiculo = atual->prox;
        free(atual);
        atual = proximoVeiculo;
    }
}

int main() {
    Veiculo* listaVeiculos = inicializarLista();

    int opcao;

    do {
        printf("\n1 - Adicionar Veiculo\n");
        printf("2 - Listar Diesel Ano 2010 ou Posterior\n");
        printf("3 - Listar Placas com Letra J\n");
        printf("4 - Listar Modelo e Cor com Placas Especificas\n");
        printf("5 - Trocar Proprietario sem Digito Zero na Placa\n");
        printf("0 - Sair\n");

        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarVeiculo(&listaVeiculos);
                break;
            case 2:
                Diesel2010(listaVeiculos);
                break;
            case 3:
                PlacasJ(listaVeiculos);
                break;
            case 4:
                verificarVogalSoma(listaVeiculos);
                break;
            case 5:
                trocarProprietario(&listaVeiculos);
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);

    liberarVeiculos(listaVeiculos);

    return 0;
}
