#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"

static char *read_file(const char *path) {
    FILE *f = fopen(path, "rb");
    if (!f) {
        fprintf(stderr, "erisc: could not open '%s'\n", path);
        exit(1);
    }

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *buf = malloc(size + 1);
    fread(buf, 1, size, f);
    buf[size] = '\0'; /* Null-terminate the string */

    fclose(f);
    return buf;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: erisc <file.eris>\n");
        return 1;
    }

    const char *src = read_file(argv[1]);

    Lexer lx;
    lexer_init(&lx, src);

    Token t = lexer_next(&lx);
    while (t.kind != TOK_EOF) {
        printf("TOK_INT: %ld\n", t.ival);
        t = lexer_next(&lx);
    }
    printf("End of File\n");

    return 0;
}