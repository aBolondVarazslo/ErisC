#ifndef LEXER_H
#define LEXER_H

typedef enum {
    TOK_EOF, /* No more input/End Of File */
    TOK_INT, /* Integer literal */
    TOK_IDENT, /* Identifier */

    /* Keywords */
    TOK_FN, /* Function keyword */
    TOK_LET, /* Let keyword */
    TOK_RET, /* Return keyword */
    TOK_IF, /* If keyword */
    TOK_ELSE, /* Else keyword */
    TOK_WHILE, /* While keyword */
    TOK_FOR, /* For keyword */
    TOK_BRIDGE, /* Extern keyword */
    TOK_TRUE, /* True keyword */
    TOK_FALSE, /* False keyword */
} TokenKind;

typedef struct {
    TokenKind kind;
    long ival; /* Integer value */
    char *text; /* Text representation of the token (for identifiers) */
} Token;

typedef struct {
    const char *src; /* Source code */
    int pos; /* Current position in the source code */
} Lexer;

void lexer_init(Lexer *lx, const char *src);
Token lexer_next(Lexer *lx);

#endif