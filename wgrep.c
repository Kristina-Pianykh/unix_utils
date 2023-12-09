#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int grep(FILE *stream, const char *substr) {

	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	while ((nread = getline(&line, &len, stream)) != -1) {
		if ( strstr(line, substr) != NULL ) {
			fwrite(line, nread, 1, stdout);
		}
	}

	free(line);
	fclose(stream);
	return EXIT_SUCCESS;
}


int main(int argc, char *argv[]) {

	const char *substr;

	if (argc == 2) {
		substr = argv[1];
		
		if ( grep(stdin, substr) != 0 ) {
			exit(EXIT_FAILURE);
		}

	} else if (argc == 3) {

		char *file_name = argv[2];
		substr = argv[1];

		FILE *stream = fopen(file_name, "r");

		if (stream == NULL) {
				printf("wgrep: cannot open file\n");
				return EXIT_FAILURE;
		}

		if ( grep(stream, substr) != 0 ) {
			exit(EXIT_FAILURE);
		}

	} else {
		printf("wgrep: searchterm [file ...]\n");
		exit(EXIT_FAILURE);
	}
	return EXIT_SUCCESS;
}

