#include <ctype.h>
#include <stdlib.h>
#include "lexer.h"

void lexer_init(Lexer *lx, const char *src)
{
    lx->src = src;
    lx->pos = 0;
}

Token lexer_next(Lexer *lx)
{
    /* Skip whitespace */
    while (lx->src[lx->pos] == ' ' || lx->src[lx->pos] == '\n' || lx->src[lx->pos] == '\t')
    {
        lx->pos++;
    }

    char c = lx->src[lx->pos];

    if (c == '\0')
    {
        Token t = {TOK_EOF, 0};
        return t;
    }

    if (isdigit((unsigned char)c))
    {
        int start = lx->pos;
        while (isdigit((unsigned char)lx->src[lx->pos]))
        {
            lx->pos++; /* Keep consuming digits until not a digit */
        }
        int len = lx->pos - start;

        char buf[32]; /* Buffer to hold the integer string */
        for (int i = 0; i < len; i++)
        {
            buf[i] = lx->src[start + i];
        }
        buf[len] = '\0'; /* Null-terminate the string */

        Token t = {TOK_INT, strtol(buf, NULL, 10)}; /* Convert string to long */
        return t;

        lx->pos++;             /* Move past the integer literal */
        return lexer_next(lx); /* Continue lexing after the integer literal */
    }
}