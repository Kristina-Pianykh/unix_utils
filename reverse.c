#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


struct node {
    struct node *prev;
    struct node *next;
    char *line;
};


struct linked_list {
    struct node *last_node;
};


struct node *alloc_node() {
    struct node *next_node = calloc(1, sizeof(struct node *));

    if (next_node == NULL) {
        fprintf(stderr, "Node allocation failed\n");
        exit(EXIT_FAILURE);
    }

    return next_node;
}


char *alloc_line(size_t nbytes) {
    char *line = calloc(1, nbytes);

    if (line == NULL) {
        fprintf(stderr, "Line allocation failed\n");
        exit(EXIT_FAILURE);
    }

    return line;
}


FILE *open_file(char *file_name, char *mode) {
    FILE *stream;

    stream = fopen(file_name, mode);
    if (stream == NULL) {
        fprintf(stderr, "error: cannot open file: %s\n", file_name);
        exit(EXIT_FAILURE);
    }
    return stream;
}

void traverse_print_lst(struct linked_list *linked_list, FILE *out_stream) {
    struct node *node = linked_list->last_node;

    while (node != NULL) {
        fprintf(out_stream, "%s", node->line);
        node = node->prev;
    }
}

void free_nodes(struct linked_list *linked_list, FILE *out_stream) {
    struct node *node = linked_list->last_node;

    while (node != NULL) {

        if (node->next != NULL) {
            free(node->next->line);
            free(node->next);
        }

        if (node->prev == NULL) {
            free(node->line);
            free(node);
            node = NULL;
        } else {
            node = node->prev;
        }
    }
}

void append(struct linked_list *linked_list, char *line, size_t nbytes) {
    /* struct node *node = calloc(1, sizeof(struct node)); */
    struct node *node = alloc_node();
    node->prev = linked_list->last_node;
    node->next = NULL;
    /* node->line = (char *) malloc(nbytes); */
    node->line = alloc_line(nbytes);
    memcpy(node->line, line, nbytes);

    if ( linked_list->last_node != NULL ) {
        linked_list->last_node->next = node;
    }

    linked_list->last_node = node;
}

void reverse(FILE *in_stream, FILE *out_stream, struct linked_list linked_list) {
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    while ((nread = getline(&line, &len, in_stream)) != -1) {
      append(&linked_list, line, nread);
    }

    traverse_print_lst(&linked_list, out_stream);
    free_nodes(&linked_list, out_stream);
    free(line);
}


int main(int argc, char *argv[]) {
    char *in_file;
    char *out_file;
    FILE *in_stream;
    FILE *out_stream;
    struct linked_list linked_list = { NULL };

    switch (argc) {
        case 1:
            reverse(stdin, stdout, linked_list);
            break;
        case 2:
            in_file = argv[1];
            in_stream = open_file(in_file, "r");
            reverse(in_stream, stdout, linked_list);
            fclose(in_stream);
            break;
        case 3:
            in_file = argv[1];
            out_file = argv[2];

            if (strcmp(in_file, out_file) == 0) {
                fprintf(stderr, "Input and output file must differ\n");
                exit(EXIT_SUCCESS);
            }

            in_stream = open_file(in_file, "r");
            out_stream = open_file(out_file, "w+");

            reverse(in_stream, out_stream, linked_list);

            fclose(in_stream);
            fclose(out_stream);
            break;
        default:
            fprintf(stderr, "usage: reverse <input> <output>\n");
            exit(EXIT_FAILURE);
    }
}
