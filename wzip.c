#include <stdio.h>
#include <stdbool.h> 
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


unsigned int ch;
unsigned int prev_ch = '\0';
unsigned int count = 0;
unsigned char buffer[5] = {0};


int write_buffer(unsigned int *count, unsigned int ch, unsigned char *buffer) {
    /* FILE *ptr; */
    /* printf("we are in the write_buffer() function\n"); */
    /*  */
    /* printf("count value: %u\n", *count); */
    /* printf("char to write: %c\n", (char)ch); */
    /* printf("buffer address: %hhn\n", buffer); */
    memcpy(buffer, count, sizeof(unsigned int));
    /* printf("char %c\n", (char)ch); */
    memcpy(buffer + 4, &ch, sizeof(char));

    // Print the array elements
    /* for (size_t i = 0; i < sizeof(buffer); i++) { */
    /*     printf("%d ", buffer[i]); */
    /* } */

    /* ptr = fopen(file,"a+"); */

    /* printf("size of buffer: %lu\n", sizeof(buffer)); */
    /* printf("1st char of buffer: %u\n", buffer[0]); */
    /* printf("2st char of buffer: %u\n", buffer[1]); */
    /* printf("3st char of buffer: %u\n", buffer[2]); */
    /* printf("4st char of buffer: %u\n", buffer[3]); */
    /* printf("5st char of buffer: %u\n", buffer[4]); */

    /* size_t ret = fwrite(buffer, 5, 1, ptr); */
		fwrite(buffer, 5, 1, stdout);

    /* if (ret != sizeof(*buffer)) { */
    /*     fprintf(stderr, "fread() failed: %lu\n", ret); */
    /*     return EXIT_FAILURE; */
    /* } */
    /* fclose(ptr); */
    return EXIT_SUCCESS;
}


/* void reset_buffer(unsigned char *buffer) { */
/*     memset(buffer, 0, 5); */
/* } */
/*  */
bool buffer_is_empty(unsigned char *buffer) {
    for (size_t i = 0; i < 5; i++) {
        if ( *(buffer + i) != 0 ) {
            return false;
        }
    }
    return true;
}


int compress_file(FILE *stream) {

    while ( (ch = fgetc(stream)) != EOF ) {

        if (prev_ch == '\0' && count == 0) {
            /* printf("The very first char %c\n", (char)ch); */
            prev_ch = ch;
            count++;
            continue;
        }

        if ( (int)ch == (int)prev_ch ) {
            /* printf("same char as the previous char %c\n", (char)ch); */
            count++;
        } else {
            /* printf("different new char type: %c\n", (char)ch); */
            /* printf("previous char: %c\n", (char)prev_ch); */
            /* printf("writing buffer\n"); */
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
    /* const char *file_name = "test.bin"; */
    FILE *stream;
    int idx = 1;

    /* printf("buffer address: %hhn\n", buffer); */

    if (argc < 2) {
      printf("wzip: file1 [file2 ...]\n");
      exit(EXIT_FAILURE);
    }

    /* printf("number of passed files: %d\n", argc - 1); */
    /* printf("argc = %d\n", argc); */

    while (argc > idx) {
        /* printf("File %s\n", argv[idx]); */
        stream = fopen(argv[idx++], "r"); 
        /* printf("current idx value: %d\n", idx); */

        if (stream == NULL) { 
            printf("wzip: cannot open file\n");
            exit(EXIT_FAILURE);
        }
        int rc = compress_file(stream);
        if ( rc != EXIT_SUCCESS ) {
            exit(EXIT_FAILURE);
        }
        /* printf("count: %u\n", count); */
        /* printf("ch: %c\n", prev_ch); */
    }
    /* printf("size of buffer: %lu\n", sizeof(buffer)); */
    /* printf("1st char of buffer: %u\n", buffer[0]); */
    /* printf("2st char of buffer: %u\n", buffer[1]); */
    /* printf("3st char of buffer: %u\n", buffer[2]); */
    /* printf("4st char of buffer: %u\n", buffer[3]); */
    /* printf("5st char of buffer: %u\n", buffer[4]); */
    if ( buffer_is_empty(buffer) == true ) {
        /* printf("buffer is empty\n"); */
        int rc = write_buffer(&count, prev_ch, buffer);
        if ( rc != EXIT_SUCCESS ) {
            exit(EXIT_FAILURE);
        }
    }
}
