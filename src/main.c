#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"

static char *read_file(const char *path)
{
    FILE *f = fopen(path, "rb");
    if (!f)
    {
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

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: erisc <file.eris>\n");
        return 1;
    }

    const char *src = read_file(argv[1]);

    Lexer lx;
    lexer_init(&lx, src);

    Token t = lexer_next(&lx);
    while (t.kind != TOK_EOF)
    {
        switch (t.kind)
        {
        case TOK_INT:
            printf("TOK_INT: %ld\n", t.ival);
            break;
        case TOK_IDENT:
            printf("TOK_IDENT: %s\n", t.text);
            break;
        case TOK_FN:
            printf("TOK_FN\n");
            break;
        case TOK_LET:
            printf("TOK_LET\n");
            break;
        case TOK_RET:
            printf("TOK_RET\n");
            break;
        case TOK_IF:
            printf("TOK_IF\n");
            break;
        case TOK_ELSE:
            printf("TOK_ELSE\n");
            break;
        case TOK_WHILE:
            printf("TOK_WHILE\n");
            break;
        case TOK_FOR:
            printf("TOK_FOR\n");
            break;
        case TOK_BRIDGE:
            printf("TOK_BRIDGE\n");
            break;
        case TOK_TRUE:
            printf("TOK_TRUE\n");
            break;
        case TOK_FALSE:
            printf("TOK_FALSE\n");
            break;
        case TOK_EOF:
            break;
        }
        t = lexer_next(&lx);
    }
    printf("End of File\n");

    return 0;
}