#include <stdio.h>
#include <stdbool.h> 
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


unsigned int ch;
unsigned int ch_count = 0;
unsigned char buffer[5] = {0};
size_t buffer_size = sizeof(buffer) / sizeof(buffer[0]);


void reset_buffer(unsigned char *buffer) {
    memset(buffer, 0, 5);
}


void decompress_file(FILE *stream) {
    unsigned char ch_count[4] = {0};
    unsigned char bytes_read;

    while (( bytes_read = fread(buffer, buffer_size, 1, stream)) == 1) {
    memcpy(ch_count, buffer, 4);

    for (unsigned int i = 1; i <= *(int *)ch_count; i++) { /* converting buffer to int * is dependant on the system endiannes */
        printf("%c", buffer[4]);
    }
    reset_buffer(buffer);
    }
}


int main(int argc, char *argv[]) {
    FILE *stream;
    int idx = 1;

    if (argc < 2) {
      printf("wunzip: file1 [file2 ...]\n");
      exit(EXIT_FAILURE);
    }

    while (argc > idx) {
        stream = fopen(argv[idx++], "rb"); 

        if (stream == NULL) { 
            printf("wunzip: cannot open file\n");
            exit(EXIT_FAILURE);
        }
        decompress_file(stream);
    }
}
