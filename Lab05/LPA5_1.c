#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void gerar_palavras_auxiliar(char *palavra, int posicao, int tamanho_maximo, char *caracteres) {
    if (posicao == tamanho_maximo) {
        printf("%s\n", palavra);
        return;
    }

    for (int i = 0; caracteres[i] != '\0'; i++) {
        palavra[posicao] = caracteres[i];
        gerar_palavras_auxiliar(palavra, posicao + 1, tamanho_maximo, caracteres);
    }
}

void gerar_palavras(int tamanho_maximo, char *caracteres) {
    char *palavra = (char *)malloc((tamanho_maximo + 1) * sizeof(char));

    if (palavra == NULL) {
        printf("SEM PALAVRAS PRA VOCE.\n");
        return;
    }

    for (int tamanho = 1; tamanho <= tamanho_maximo; tamanho++) {
        for (int i = 0; i < tamanho; i++) {
            palavra[i] = '\0';
        }
        gerar_palavras_auxiliar(palavra, 0, tamanho, caracteres);
    }

    free(palavra);
}

int main() {
    printf("tamanho da STRING: ");
    int tamanhoMaximo;
    scanf("%d", &tamanhoMaximo);

    char caracteres[100]; 
    printf("STRING: ");
    scanf("%s", caracteres);

    gerar_palavras(tamanhoMaximo, caracteres);

    return 0;
}
