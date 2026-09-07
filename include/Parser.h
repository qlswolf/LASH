// Parser: Creates an abstract syntax tree (AST) with the tokens given.

#ifndef PARSER_H
#define PARSER_H

typedef enum s_ASTtype
{
    AST_COMMAND, // Command (Words)
    AST_AND,     // AND
    AST_OR       // OR
} t_ASTtype;

typedef struct s_Wordcommand    // One command could consist of multiple Words one after another, so we use a linked list again.
{
    char *value;
    struct s_Wordcommand *next;
} t_Wordcommand;

typedef struct s_AST
{                         // struct for the AST
    t_ASTtype type;       // type of Node
    t_Wordcommand *words; // words of the wordcommand
    struct s_AST *left;   // left side of the AST
    struct s_AST *right;  // right side of the AST
} t_AST;

// example:     echo hello world && ls
//
//                       AND
//                    /       \
//              Command        Command
//            /    |    \          |
//       "echo" "hello" "world"   "ls"

#endif