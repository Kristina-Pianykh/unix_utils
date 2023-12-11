#include <stdio.h>
#include <stdbool.h> 
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char *argv[]) {
    FILE *stream = fopen("1a.in", "r"); 
    char ch;

    while ( (ch = fgetc(stream)) != EOF ) {
        printf("%d\n", (int) ch);
    }
}
