#ifndef PARSER_H
#define PARSER_H

#include "Lexer.h"

typedef enum s_NodeType {
    NODE_COMMAND,
    NODE_PIPE
} t_NodeType;

typedef struct s_Node {
    t_NodeType type;            // Type of the AST node
    char **args;                // Arguments for command nodes
    struct s_Node *left;     // Left child (for pipe nodes)
    struct s_Node *right;    // Right child (for pipe nodes)
} t_Node;

typedef struct s_Redirect {
    t_TokenType type;
    char *filename;
    struct s_Redirect *next;
} t_Redirect;

#endif /* PARSER_H */