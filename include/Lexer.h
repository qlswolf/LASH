// Lexer: Defines the token types and structures for the lexer component of the project.

#ifndef LEXER_H
#define LEXER_H

/** Token types for the Lexer */

typedef enum s_TokenType {
    TOKEN_WORD,
    TOKEN_PIPE,
    TOKEN_REDIRECT_IN,
    TOKEN_REDIRECT_OUT,
    TOKEN_AND,
    TOKEN_OR,
    TOKEN_EOF
} t_TokenType;

typedef struct s_Token {
    t_TokenType type;       // Type of the token
    char *value;            // The actual string value of the token
    struct s_Token *next;   // Pointer to the next token in the list
} t_Token;

void free_tokens(t_Token *head);

t_Token *lexer(char *input);

#endif LEXER_H