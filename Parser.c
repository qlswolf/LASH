#include "Parser.h"
#include <stdio.h>

static t_Node *create_Node(t_NodeType type) {
    t_Node *node = malloc(sizeof(t_Node));
    if (!node) {
        printf("Error: Memory allocation for node failed.\n");
        return NULL;
    }
    node->type = type;
    node->args = NULL;
    node->left = NULL;
    node->right = NULL;
    return node;
}

static t_Redirect *create_Redirect(t_TokenType type, char *filename) {
    t_Redirect *redirect = malloc(sizeof(t_Redirect));
    if (!redirect) {
        printf("Error: Memory allocation for redirect failed.\n");
        return NULL;
    }
    redirect->type = type;
    redirect->filename = filename;
    redirect->next = NULL;
    return redirect;
}

static char **copy_args(char **args, int count) {
    char **arr = malloc((count + 1) * sizeof(char));
    if (!arr) {
        printf("Error: Memory allocation for args failed.\n");
        return NULL;
    }
    for (int i = 0; i < count; i++) {
        arr[i] = args[i];
    }
    arr[count] = NULL;
    return arr;
}

static t_Redirect *parse_redirects(t_Token *token) {
    t_Redirect *head = NULL;
    t_Redirect *current = NULL;

    while (token && (token->type == REDIRECT_IN || token->type == REDIRECT_OUT)) {
        if (!token->next) {
            printf("Error: Redirect operator without filename.\n");
            return NULL;
        }
        t_Redirect *redirect = create_Redirect(token->type, token->next->value);
        if (!head) {
            head = redirect;
            current = redirect;
        } else {
            current->next = redirect;
            current = redirect;
        }
        token = token->next->next;
    }
    return head;
}

static t_Node *parse_command(t_Token *token) {
    t_Node *node = create_Node(NODE_COMMAND);
    if (!node) {
        return NULL;
    }
    
    int count = 0;
    t_Token *current = token;
    while (current && current->type == WORD) {
        count++;
        current = current->next;
    }
    node->args = copy_args(token, count);
    return node;
}