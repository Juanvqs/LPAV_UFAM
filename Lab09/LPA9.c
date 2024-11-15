#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SEQUENCE_HEADER "\x00\x00\x01\xB3"

int main(int argc, unsigned char *argv[]) {
    int part = 1;
    int ocup = 0;
    int tamArquivo = 0;
    int sequencia = 0;

    FILE *arq = fopen(argv[1], "rb");
    if (arq == NULL) {
        perror ("erro");
    }
    FILE *parte = fopen("video_parte_1.mpg", "wb");
    if (parte == NULL) {
        return 1;
    }
    char *bytes = malloc(sizeof(char) * 4);
    if (bytes == NULL) {
        return 1;
    }
    int tamanho_maximo = atoi(argv[2]);
    int tamanho_buffer = tamanho_maximo * 1000000;
    unsigned char *buffer = calloc(tamanho_buffer + 1, sizeof(char));


    while (1) {
        if (!sequencia) {
            fread(bytes, sizeof(char), 4, arq);
            if (memcmp(bytes, SEQUENCE_HEADER, 4) == 0) {
                sequencia = 1;
                memcpy(buffer, bytes, 4);
                ocup = 4;
            } else {
                fseek(arq, -3, SEEK_CUR);
            }
        } else {
            int bytes_lidos = fread(buffer + ocup, sizeof(char), tamanho_buffer - ocup, arq);
            ocup += bytes_lidos;
            if (ocup >= tamanho_buffer || feof(arq)) {
                fclose(parte);
                char nomeDoArqv[100];
                printf("Criando arquivo video_part_%d.mpg ..\n", part);
                sprintf(nomeDoArqv, "video_parte_%d.mpg", part);
                parte = fopen(nomeDoArqv, "wb");
                fwrite(buffer, sizeof(char), ocup, parte);
                tamArquivo = ocup;
                ocup = 0;
                part++;
                sequencia = 0;
            }
        }

        if (feof(arq)) {
            fclose(parte);
            break;
        }
    }

    free(buffer);
    fclose(arq);

    return 0;
}