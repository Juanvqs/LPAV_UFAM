#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <arpa/inet.h>

struct png_chunk_hdr {
    uint32_t length;
    char type[4];
} __attribute__((__packed__));

struct png_ihdr_chunk {
    uint32_t width;
    uint32_t height;
    uint8_t bit_depth;
    uint8_t color_type;
    uint8_t compression;
    uint8_t filter;
    uint8_t interlace;
} __attribute__((__packed__));

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s ferrari.png\n", argv[0]);
        return 1;
    }

    FILE *png_file = fopen(argv[1], "rb");
    if (!png_file) {
        perror("Erro ao abrir o arquivo PNG");
        return 1;
    }

    fseek(png_file, 8, SEEK_SET);

    int chunk_count = 0;
    struct png_chunk_hdr png_chunk; // Declaração de png_chunk

    while (fread(&png_chunk, sizeof(struct png_chunk_hdr), 1, png_file) == 1) {
        chunk_count++;
        uint32_t chunk_size = ntohl(png_chunk.length);
        char chunk_type[5];
        strncpy(chunk_type, png_chunk.type, 4);
        chunk_type[4] = '\0';

        printf("Lendo chunk %d:\n", chunk_count);
        printf(" --> Tamanho: %u\n", chunk_size);
        printf(" --> Tipo: %s\n", chunk_type);

        if (strncmp(chunk_type, "IHDR", 4) == 0) {
            struct png_ihdr_chunk ihdr_chunk;
            if (fread(&ihdr_chunk, sizeof(struct png_ihdr_chunk), 1, png_file) != 1) {
                perror("Erro ao ler IHDR chunk");
                break; // Saia do loop se a leitura falhar
            }

            uint32_t width = ntohl(ihdr_chunk.width);
            uint32_t height = ntohl(ihdr_chunk.height);

            printf(" --> Largura: %u\n", width);
            printf(" --> Altura: %u\n", height);

            fseek(png_file, 4, SEEK_CUR);
        } else {
            fseek(png_file, chunk_size + 4, SEEK_CUR);
        }
    }

    fclose(png_file);

    return 0;
}
