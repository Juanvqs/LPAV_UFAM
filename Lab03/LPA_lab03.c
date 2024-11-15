#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

typedef struct lista_vizinhos_t {
    struct lista_vizinhos_t *proximo;
    int vizinho;
} lista_vizinhos_t;

typedef struct no_t {
    int id;
    double pos_x;
    double pos_y;
    lista_vizinhos_t *lista_vizinhos;
} no_t;

typedef no_t* grafo_t;

bool lista_vizinhos_adicionar(int vizinho, lista_vizinhos_t **lista) {
    lista_vizinhos_t *item_novo = (lista_vizinhos_t*)malloc(sizeof(lista_vizinhos_t));
    if (item_novo == NULL) {
        return false;
    } else {
        item_novo->vizinho = vizinho;
        item_novo->proximo = *lista;
        *lista = item_novo;
        return true;
    }
}

void grafo_atualizar_vizinhos(int tam, double raio_comunicacao, grafo_t grafo) {
    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++) {
            if (i != j) {
                double distancia = sqrt(pow(grafo[i].pos_x - grafo[j].pos_x, 2) + pow(grafo[i].pos_y - grafo[j].pos_y, 2));
                if (distancia < raio_comunicacao) {
                    lista_vizinhos_adicionar(j, &grafo[i].lista_vizinhos);
                }
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s LAB03.txt\n", argv[0]);
        return 1;
    }

    FILE *arquivo = fopen(argv[1], "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    int num_nos;
    double raio_comunicacao;

    fscanf(arquivo, "%d\t%lf\n", &num_nos, &raio_comunicacao);

    grafo_t grafo = (grafo_t)malloc(sizeof(no_t) * num_nos);
    if (grafo == NULL) {
        printf("Erro ao alocar memória para o grafo.\n");
        return 1;
    }

    for (int i = 0; i < num_nos; i++) {
        fscanf(arquivo, "%d\t%lf\t%lf\n", &grafo[i].id, &grafo[i].pos_x, &grafo[i].pos_y);
        grafo[i].lista_vizinhos = NULL;
    }

    fclose(arquivo);

    grafo_atualizar_vizinhos(num_nos, raio_comunicacao, grafo);

    
    for (int i = 0; i < num_nos; i++) {
        printf("Nó %d (%lf, %lf) -> Vizinhos:", grafo[i].id, grafo[i].pos_x, grafo[i].pos_y);
        lista_vizinhos_t *vizinho_atual = grafo[i].lista_vizinhos;
        while (vizinho_atual) {
            printf(" %d", vizinho_atual->vizinho);
            vizinho_atual = vizinho_atual->proximo;
        }
        printf("\n");
    }

    free(grafo);

    return 0;
}
