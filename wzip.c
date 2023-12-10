#include <stdio.h>
/* #include <stdbool.h>  */
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int wzip(FILE *stream) {
    unsigned int ch;
    unsigned int prev_ch = 0;
    int count = 0;
    unsigned char buffer[5] = {0};
    FILE *ptr;

    while ( (ch = fgetc(stream)) != EOF ) {

        if ( (int)ch == (int)prev_ch ) {
            prev_ch = ch;
            count++;
        } else {
            memcpy(buffer, &count, sizeof(int));
            printf("char %c\n", (char)ch);
            memcpy(&buffer[4], &prev_ch, sizeof(char));

            // Print the array elements
            for (size_t i = 0; i < sizeof(buffer); i++) {
                printf("%d ", buffer[i]);
            }

            ptr = fopen("test.bin","a+");

            printf("size of buffer: %lu\n", sizeof(buffer));
            printf("1st char of buffer: %u\n", buffer[0]);
            printf("2st char of buffer: %u\n", buffer[1]);
            printf("3st char of buffer: %u\n", buffer[2]);
            printf("4st char of buffer: %u\n", buffer[3]);
            printf("5st char of buffer: %u\n", buffer[4]);

            size_t ret = fwrite(&buffer, 5, 1, ptr);

            if (ret != sizeof(*buffer)) {
                fprintf(stderr, "fread() failed: %lu\n", ret);
                exit(EXIT_FAILURE);
            }
            fclose(ptr);
            prev_ch = ch;
            count = 1;
        }
    }
	return EXIT_SUCCESS;
}


int main(int argc, char *argv[]) {
    FILE *stream;
    /* int rc; */
    int idx = 1;

	if (argc < 2) {
		printf("No file is passed.\nUsage: wcat <file>\n");
		exit(0);
	}
    while (argc > idx) {
        stream = fopen(argv[idx++], "r");

        if (stream == NULL) { 
            printf("wzip: cannot open file\n");
            exit(EXIT_FAILURE);
    }
    wzip(stream);
		
		/* if (rc != 0) { */
		/* 	exit(EXIT_FAILURE); */
		/* } */
  /*  */
	}
}

