#include <stdio.h>
#include <string.h>

struct Carta {
    char estado;
    int numero;
    char nomeCidade[50];
    unsigned long int populacao;
    float area;
    float pib;
    int pontosTuristicos;
    float densidade;
    float pibPerCapita;
};

// Funcao para calcular atributos derivados
void calcularAtributos(struct Carta* c) {
    c->densidade = c->populacao / c->area;
    c->pibPerCapita = c->pib / c->populacao;
}

// Funcao para mostrar uma carta
void exibirCarta(struct Carta c) {
    printf("Codigo: %c%02d\n", c.estado, c.numero);
    printf("Cidade: %s\n", c.nomeCidade);
    printf("Populacao: %lu\n", c.populacao);
    printf("Area: %.2f km2\n", c.area);
    printf("PIB: %.2f bilhoes\n", c.pib);
    printf("Pontos Turisticos: %d\n", c.pontosTuristicos);
    printf("Densidade Populacional: %.2f hab/km2\n", c.densidade);
    printf("PIB per Capita: %.6f\n", c.pibPerCapita);
}

// Funcao para comparar dois atributos
int comparar(float v1, float v2, int inverso) {
    if (v1 == v2) return -1; // empate
    return (inverso ? (v1 < v2) : (v1 > v2)) ? 1 : 2;
}

// Funcao para imprimir resultado da comparacao
void resultado(int r, char atributo[]) {
    if (r == -1)
        printf("Empate no atributo %s!\n", atributo);
    else
        printf("Carta %d venceu no atributo %s!\n", r, atributo);
}

int main() {
    struct Carta c1, c2;
    int opcao1, opcao2;

    // Cadastro carta 1
    printf("Cadastro da Carta 1\n");
    printf("Estado (A-H): ");
    scanf(" %c", &c1.estado);
    printf("Numero da cidade (1-4): ");
    scanf("%d", &c1.numero);
    printf("Nome da cidade: ");
    scanf(" %[^\n]", c1.nomeCidade);
    printf("Populacao: ");
    scanf("%lu", &c1.populacao);
    printf("Area (km2): ");
    scanf("%f", &c1.area);
    printf("PIB (bilhoes): ");
    scanf("%f", &c1.pib);
    printf("Pontos turisticos: ");
    scanf("%d", &c1.pontosTuristicos);
    calcularAtributos(&c1);

    // Cadastro carta 2
    printf("\nCadastro da Carta 2\n");
    printf("Estado (A-H): ");
    scanf(" %c", &c2.estado);
    printf("Numero da cidade (1-4): ");
    scanf("%d", &c2.numero);
    printf("Nome da cidade: ");
    scanf(" %[^\n]", c2.nomeCidade);
    printf("Populacao: ");
    scanf("%lu", &c2.populacao);
    printf("Area (km2): ");
    scanf("%f", &c2.area);
    printf("PIB (bilhoes): ");
    scanf("%f", &c2.pib);
    printf("Pontos turisticos: ");
    scanf("%d", &c2.pontosTuristicos);
    calcularAtributos(&c2);

    // Exibicao
    printf("\n--- Carta 1 ---\n");
    exibirCarta(c1);
    printf("\n--- Carta 2 ---\n");
    exibirCarta(c2);

    // Menu de comparacao
    printf("\n=== MENU DE COMPARACAO ===\n");
    printf("1 - Populacao\n");
    printf("2 - Area\n");
    printf("3 - PIB\n");
    printf("4 - Pontos Turisticos\n");
    printf("5 - Densidade Populacional (menor vence)\n");
    printf("6 - PIB per Capita\n");
    printf("Escolha o primeiro atributo para comparar: ");
    scanf("%d", &opcao1);
    printf("Deseja comparar um segundo atributo? (1 - Sim, 0 - Nao): ");
    scanf("%d", &opcao2);

    int segundaOpcao = 0;
    if (opcao2) {
        printf("Escolha o segundo atributo para comparar: ");
        scanf("%d", &segundaOpcao);
    }

    // Comparacoes
    float v1a = 0, v2a = 0, v1b = 0, v2b = 0;
    char nome1[30], nome2[30];
    int inv1 = 0, inv2 = 0;

    // Atributo 1
    switch (opcao1) {
        case 1: v1a = c1.populacao; v2a = c2.populacao; strcpy(nome1, "Populacao"); break;
        case 2: v1a = c1.area; v2a = c2.area; strcpy(nome1, "Area"); break;
        case 3: v1a = c1.pib; v2a = c2.pib; strcpy(nome1, "PIB"); break;
        case 4: v1a = c1.pontosTuristicos; v2a = c2.pontosTuristicos; strcpy(nome1, "Pontos Turisticos"); break;
        case 5: v1a = c1.densidade; v2a = c2.densidade; strcpy(nome1, "Densidade Populacional"); inv1 = 1; break;
        case 6: v1a = c1.pibPerCapita; v2a = c2.pibPerCapita; strcpy(nome1, "PIB per Capita"); break;
        default: printf("Opcao invalida!\n"); return 1;
    }

    int resultado1 = comparar(v1a, v2a, inv1);

    if (opcao2 && segundaOpcao >= 1 && segundaOpcao <= 6) {
        switch (segundaOpcao) {
            case 1: v1b = c1.populacao; v2b = c2.populacao; strcpy(nome2, "Populacao"); break;
            case 2: v1b = c1.area; v2b = c2.area; strcpy(nome2, "Area"); break;
            case 3: v1b = c1.pib; v2b = c2.pib; strcpy(nome2, "PIB"); break;
            case 4: v1b = c1.pontosTuristicos; v2b = c2.pontosTuristicos; strcpy(nome2, "Pontos Turisticos"); break;
            case 5: v1b = c1.densidade; v2b = c2.densidade; strcpy(nome2, "Densidade Populacional"); inv2 = 1; break;
            case 6: v1b = c1.pibPerCapita; v2b = c2.pibPerCapita; strcpy(nome2, "PIB per Capita"); break;
            default: printf("Segunda opcao invalida!\n"); return 1;
        }

        int resultado2 = comparar(v1b, v2b, inv2);

        // Resultado final considerando empate
        printf("\n--- RESULTADO DAS COMPARACOES ---\n");
        resultado(resultado1, nome1);
        resultado(resultado2, nome2);

        if (resultado1 == resultado2 && resultado1 != -1) {
            printf("\n*** Carta %d venceu a disputa geral! ***\n", resultado1);
        } else if (resultado1 != -1 && resultado2 != -1 && resultado1 != resultado2) {
            printf("\n*** Empate na disputa geral: cada carta venceu um atributo! ***\n");
        } else {
            printf("\n*** Empate total ou comparacao inconclusiva. ***\n");
        }

    } else {
        printf("\n--- RESULTADO DA COMPARACAO ---\n");
        resultado(resultado1, nome1);
    }

    return 0;
}
