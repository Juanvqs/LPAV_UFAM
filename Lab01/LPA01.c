#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct evento_t {
    double tempo;
    int alvo;
    int tipo;
} evento_t; // tipo de evento

typedef struct lista_eventos_t {
    struct lista_eventos_t *proximo;
    evento_t evento;
} lista_eventos_t; // define como quero o tipo lista de evento (Campo com os dados e um link para o prox)

void lista_eventos_adicionar_inicio(evento_t *evento, lista_eventos_t **lista) {
    lista_eventos_t *item_novo = (lista_eventos_t*)malloc(sizeof(lista_eventos_t));
    if (item_novo == NULL) {
        return;
    } else {
        item_novo->evento = *evento;
        item_novo->proximo = *lista;
        *lista = item_novo;
    }
}

void lista_eventos_listar(lista_eventos_t *lista) {
    while (lista) {
        printf("Tempo: %f, Alvo: %d, Tipo: %d\n", lista->evento.tempo, lista->evento.alvo, lista->evento.tipo);
        lista = lista->proximo;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s Lpa01.txt", argv[0]);
        return 1;
    }

    FILE *arquivo = fopen(argv[1], "r");
    if (arquivo == NULL) {
        printf("ERRRRRRRRRO\n");
        return 1;
    }

    lista_eventos_t *lista_teste = NULL;
    double tempo;
    int alvo, tipo;

    while (fscanf(arquivo, "%lf\t%d\t%d\n", &tempo, &alvo, &tipo) == 3) {
        evento_t novo_evento = {tempo, alvo, tipo};
        lista_eventos_adicionar_inicio(&novo_evento, &lista_teste);
    }

    fclose(arquivo);

    lista_eventos_listar(lista_teste);
    
    return 0;
}
