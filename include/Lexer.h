// Lexer: Splits the command into different tokens.

#ifndef LEXER_H
#define LEXER_H

/* Token types for the Lexer */

typedef enum s_TokenType {
    TOKEN_WORD,             // Token for every normal word
    TOKEN_AND,              // Token for '&&'
    TOKEN_OR,               // Token for '||'
    TOKEN_EOF               // Token for EndOfFile
} t_TokenType;

typedef struct s_Token {
    t_TokenType type;       // Type of the token
    char *value;            // The actual string value of the token (for a word)
    struct s_Token *next;   // Pointer to the next token in the list (linked list)
} t_Token;

// We could also use a dynamic array to process the command.

t_Token *lexer(char **input);

#endif