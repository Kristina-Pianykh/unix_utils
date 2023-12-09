#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int cat_file(char *file) {
	FILE *stream;
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	stream = fopen(file, "r");
	if (stream == NULL) {
			printf("wcat: cannot open file\n");
			exit(EXIT_FAILURE);
	}

	while ((nread = getline(&line, &len, stream)) != -1) {
		fwrite(line, nread, 1, stdout);
	}

	free(line);
	fclose(stream);
	return 0;
}


int main(int argc, char *argv[]) {
	int argcount = argc;

	if (argc < 2) {
		printf("No file is passed.\nUsage: wcat <file>\n");
		exit(0);
	}
	while (argc > 1) {
		int rc = cat_file(argv[argcount - --argc]);
		
		if (rc != 0) {
			exit(EXIT_FAILURE);
		}

	}
}

