#include <stdio.h>
#include <stdbool.h> 
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


unsigned int ch;
unsigned int prev_ch = '\0';
unsigned int count = 0;
unsigned char buffer[5] = {0};


void reset_buffer(unsigned char *buffer) {
    memset(buffer, 0, 5);
}


int write_buffer(unsigned int *count, unsigned int ch, unsigned char *buffer) {
    size_t nmemb = 1;

    memcpy(buffer, count, sizeof(unsigned int));
    memcpy(buffer + 4, &ch, sizeof(char));
		size_t ret = fwrite(buffer, 5, nmemb, stdout);

    if ( ret != nmemb) {
        fprintf(stderr, "fwrite() failed: %zu\n", ret);
        return EXIT_FAILURE;
    }

    reset_buffer(buffer);
    return EXIT_SUCCESS;
}


int compress_file(FILE *stream) {

    while ( (ch = fgetc(stream)) != EOF ) {

        if (prev_ch == '\0' && count == 0) {
            prev_ch = ch;
            count++;
            continue;
        }

        if ( (int)ch == (int)prev_ch ) {
            count++;
        } else {
            if (write_buffer(&count, prev_ch, buffer) != EXIT_SUCCESS) {
                return EXIT_FAILURE;
            }
            prev_ch = ch;
            count = 1;
        }
    }
    return EXIT_SUCCESS;
}


int main(int argc, char *argv[]) {
    FILE *stream;
    int idx = 1;

    if (argc < 2) {
      printf("wzip: file1 [file2 ...]\n");
      exit(EXIT_FAILURE);
    }

    while (argc > idx) {
        stream = fopen(argv[idx++], "r"); 

        if (stream == NULL) { 
            printf("wzip: cannot open file\n");
            exit(EXIT_FAILURE);
        }
        int rc = compress_file(stream);
        if ( rc != EXIT_SUCCESS ) {
            exit(EXIT_FAILURE);
        }
    }

    if ( write_buffer(&count, prev_ch, buffer) != EXIT_SUCCESS ) {
        exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}
