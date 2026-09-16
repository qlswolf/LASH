#include <stdio.h>
#include <stdlib.h>
#include <Parser.h>

static t_AST *createASTnode(t_ASTtype type) // creates Node and puts it on the heap
{
    t_AST *Node = malloc(sizeof(t_AST));
    if (!Node)
    {
        printf("Warning: memory allocation failed.\n");
        return NULL;
    }

    Node->type = type;
    Node->words = NULL;
    Node->left = NULL;
    Node->right = NULL;

    return Node;
}

static t_Wordcommand *createWord(char *value) // creates word and puts it on the heap
{
    t_Wordcommand *word = malloc(sizeof(t_Wordcommand));
    if (!word)
    {
        printf("Warning: memory allocation failed.\n");
        return NULL;
    }

    word->value = value;
    word->next = NULL;

    return word;
}

static void addWord(t_Wordcommand **head, t_Wordcommand *newWord) // word gets added to the linked list
{
    if (!*head)
    {
        *head = newWord;
        return;
    }

    t_Wordcommand *current = *head;

    while (current->next)
    {
        current = current->next;
    }

    current->next = newWord;
}

static void freeAST(t_AST *node)
{
    if (node == NULL)
    {
        return;
    }

    switch (node->type)
    {
    case AST_AND:
        freeAST(node->left);
        freeAST(node->right);
        break;
    case AST_OR:
        freeAST(node->left);
        freeAST(node->right);
        break;
    case AST_COMMAND:
        break;
    }

    free(node);
}

