#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct pessoa {
    char nome[51];
    long long int cpf;
    int idade;
} pessoa_t;

typedef struct lista_pessoas_t {
    struct lista_pessoas_t *proximo;
    pessoa_t pessoa;
} lista_pessoas_t;

typedef lista_pessoas_t** tabela_hash_t;

tabela_hash_t tabela_hash_pessoas_criar(int tamanho) {
    tabela_hash_t tabela_hash = (tabela_hash_t)malloc(sizeof(lista_pessoas_t*) * tamanho);
    if (tabela_hash == NULL) {
        return NULL;
    } else {
        for (int i = 0; i < tamanho; i++) {
            tabela_hash[i] = NULL;
        }
        return tabela_hash;
    }
}

int tabela_hash_pessoas_funcao(pessoa_t *pessoa, int tamanho) {
    return pessoa->cpf % tamanho;
}

bool lista_pessoas_adicionar(pessoa_t *pessoa, lista_pessoas_t **lista) {
    lista_pessoas_t *item_novo = (lista_pessoas_t*)malloc(sizeof(lista_pessoas_t));
    if (item_novo == NULL) {
        return false;
    } else {
        item_novo->pessoa = *pessoa;
        item_novo->proximo = *lista;
        *lista = item_novo;
        return true;
    }
}

void lista_pessoas_listar(lista_pessoas_t *lista) {
    while (lista) {
        printf("Nome: %s, CPF: %lld, Idade: %d\n", lista->pessoa.nome, lista->pessoa.cpf, lista->pessoa.idade);
        lista = lista->proximo;
    }
}

bool tabela_hash_pessoas_adicionar(pessoa_t *pessoa, tabela_hash_t tabela_hash, int tamanho) {
    if (tabela_hash == NULL) {
        return false;
    } else {
        int posicao = tabela_hash_pessoas_funcao(pessoa, tamanho);
        return lista_pessoas_adicionar(pessoa, &tabela_hash[posicao]);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s lab2_arquivo_entrada.txt\n", argv[0]);
        return 1;
    }

    int tamanho_hash = 10; 

    tabela_hash_t tabela_hash = tabela_hash_pessoas_criar(tamanho_hash);

    FILE *arquivo = fopen(argv[1], "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    pessoa_t nova_pessoa;
    while (fscanf(arquivo, "%50[^\t]\t%lld\t%d\n", nova_pessoa.nome, &nova_pessoa.cpf, &nova_pessoa.idade) == 3) {
        tabela_hash_pessoas_adicionar(&nova_pessoa, tabela_hash, tamanho_hash);
    }

    fclose(arquivo);

    tabela_hash_pessoas_listar(tabela_hash, tamanho_hash);
}
