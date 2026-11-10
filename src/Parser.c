#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Lexer.h>
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

static void freeWords(t_Wordcommand *words)
{
    t_Wordcommand *current;
    t_Wordcommand *next;

    current = words;
    while (current)
    {
        next = current->next;
        free(current->value);
        free(current);
        current = next;
    }
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
        freeWords(node->words);
        break;
    }

    free(node);
}

static t_AST *parseCommand(t_Token **current)
{
    t_AST *command = createASTnode(AST_COMMAND);
    if (!command)
    {
        freeAST(command);
        return NULL;
    }

    while ((*current)->type == TOKEN_WORD)
    {
        char *value = strdup((*current)->value);
        if (!value)
        {
            freeAST(command);
            return NULL;
        }
        t_Wordcommand *word = createWord(value);
        if (!word)
        {
            freeAST(command);
            return NULL;
        }

        addWord(&command->words, word);
        *current = (*current)->next;
    }

    return command;
}

t_AST *parser(t_Token *tokens)
{
    t_AST *head;
    t_AST *node;
    t_Token *current;

    current = tokens;

    if (!current || current->type == TOKEN_EOF)
    {
        return NULL;
    }

    head = parseCommand(&current);
    if (!head)
    {
        return NULL;
    }

    while (current && (current->type == TOKEN_AND || current->type == TOKEN_OR))
    {
        if (current->type == TOKEN_AND)
        {
            node = createASTnode(AST_AND);
        }
        else
        {
            node = createASTnode(AST_OR);
        }

        if (!node)
        {
            freeAST(head);
            return NULL;
        }

        node->left = head;
        current = current->next;

        node->right = parseCommand(&current);
        if (!node->right)
        {
            freeAST(node);
            return NULL;
        }

        head = node;
    }

    if (!current || current->type != TOKEN_EOF)
    {
        freeAST(head);
        return NULL;
    }

    return head;
}

/*
void printAST(t_AST *node, int depth)
{
    if (!node) {
        return;
    }

    for (int i = 0; i < depth; i++) {
        printf("    ");
    }

    if (node->type == AST_COMMAND)
    {
        printf("COMMAND: ");

        t_Wordcommand *word = node->words;
        while (word)
        {
            printf("%s ", word->value);
            word = word->next;
        }
        printf("\n");
    }
    else if (node->type == AST_AND)
    {
        printf("AND (&&)\n");
        printAST(node->left, depth + 1);
        printAST(node->right, depth + 1);
    }
    else if (node->type == AST_OR)
    {
        printf("OR (||)\n");
        printAST(node->left, depth + 1);
        printAST(node->right, depth + 1);
    }
}
*/