// Lexer: Defines the token types and structures for the lexer component of the project.

#ifndef LEXER_H
#define LEXER_H

/** Token types for the Lexer */

typedef enum t_TokenType {
    WORD,
    PIPE,
    REDIRECT_IN,
    REDIRECT_OUT
} t_TokenType;

typedef struct s_Token {
    t_TokenType type;       // Type of the token
    char *value;            // The actual string value of the token
    struct s_Token *next;   // Pointer to the next token in the list
} t_Token;

void free_tokens(t_Token *head);
t_Token *lexer(char *input);

#endif // LEXER_H