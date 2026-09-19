#include <stdio.h>
#include "lexer.h"

int main() {
    const char *src = "42 7 123";

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