#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"

#define NUM_KEYWORDS (int)(sizeof(KEYWORDS) / sizeof(KEYWORDS[0]))
#define NUM_TYPE_NAMES (int)(sizeof(TYPE_NAMES) / sizeof(TYPE_NAMES[0]))

typedef struct
{
    const char *word;
    TokenKind kind;
} Keyword;

static const Keyword KEYWORDS[] = {
    {"fn", TOK_FN},
    {"let", TOK_LET},
    {"ret", TOK_RET},
    {"if", TOK_IF},
    {"else", TOK_ELSE},
    {"while", TOK_WHILE},
    {"for", TOK_FOR},
    {"bridge", TOK_BRIDGE},
    {"true", TOK_TRUE},
    {"false", TOK_FALSE}};

typedef struct
{
    const char *word;
    TypeKind kind;
} TypeName;

static const TypeName TYPE_NAMES[] = {
    {"i8", TY_I8},
    {"u8", TY_U8},
    {"i16", TY_I16},
    {"u16", TY_U16},
    {"i32", TY_I32},
    {"u32", TY_U32},
    {"bool", TY_BOOL},
    {"ptr", TY_PTR},
    {"void", TY_VOID},
};

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
        Token t = {TOK_EOF, 0, NULL};
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

        Token t = {TOK_INT, strtol(buf, NULL, 10), NULL}; /* Convert string to long */
        return t;
    }

    if (isalpha((unsigned char)c) || c == '_')
    {
        int start = lx->pos;
        while (isalnum((unsigned char)lx->src[lx->pos]) || lx->src[lx->pos] == '_')
        {
            lx->pos++; /* Keep consuming alphanumeric characters and underscores */
        }
        int len = lx->pos - start;

        /* Check type-name table first */
        for (int i = 0; i < NUM_TYPE_NAMES; i++) {
            int tlen = (int)strlen(TYPE_NAMES[i].word);
            if (tlen == len && strncmp(lx->src + start, TYPE_NAMES[i].word, len) == 0) {
                Token t;
                t.kind = TOK_TYPE;
                t.ival = 0;
                t.text = NULL;
                t.type_kind = TYPE_NAMES[i].kind;
                return t;
            }
        }

        /* Check if the identifier is a keyword */
        for (int i = 0; i < NUM_KEYWORDS; i++)
        {
            int klen = (int)strlen(KEYWORDS[i].word);
            if (klen == len && strncmp(lx->src + start, KEYWORDS[i].word, len) == 0) {
                Token t;
                t.kind = KEYWORDS[i].kind;
                t.ival = 0;
                t.text = NULL;
                return t;
            }
        }

        char *name = malloc(len + 1); /* Allocate memory for the identifier string */
        for (int i = 0; i < len; i++)
        {
            name[i] = lx->src[start + i];
        }
        name[len] = '\0'; /* Null-terminate the string */

        Token t;
        t.kind = TOK_IDENT;
        t.ival = 0;
        t.text = name; /* Store the identifier string in the token */
        return t;
    }

    lx->pos++;             /* Move past the integer literal */
    return lexer_next(lx); /* Continue lexing after the integer literal */
}