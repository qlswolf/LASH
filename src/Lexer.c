#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline.h>
#include <Lexer.h>

static t_Token *create_token(t_TokenType type, char *value)     // creates token
{
    t_Token *token = malloc(sizeof(t_Token));                   // memory allocation for token

    if (!token)
    {
        printf("Warning: Memory allocation failed.\n");
        return NULL;
    }

    token->type = type;     // token definitions
    token->value = value;
    token->next = NULL;     // the next token in the list could be the last, so it is set to NULL

    return token;
}

static void addToken(t_Token **head, t_Token *newToken)     // after the token got allocated, it gets added to the linked list with this function
{
    t_Token *current;

    if (!*head)     // this is just for the first element in the list (head is always the first item in a linked list)
    {
        *head = newToken;
        return;
    }

    current = *head;

    while (current->next)       // every element is added
    {
        current = current->next;
    }

    current->next = newToken;
}

static char *readWord(char **input)     // function for reading a single word
{
    char *start;
    size_t len;

    start = *input;

    /*  We use char**, because we want to move the pointer in the string, not the char  */
    while (**input && **input != ' ' && **input != '\t' && !(**input == '&' && (*input)[1] == '&') && !(**input == '|' && (*input)[1] == '|'))
    {
        (*input)++;
    }

    len = *input - start;

    return (strndup(start, len));   // the processed word gets allocated on the heap and returned.
}

t_Token *lexer(char **input)    // lexing-function, declared in the header
{
    t_Token *head;
    t_Token *token;

    head = NULL;

    while (1)   // endless loop, ends with EOF down below
    {
        while (**input == ' ' || **input == '\t')   // skips whitespace
        {
            (*input)++;
        }

        if (**input == '\0')
        {
            token = create_token(TOKEN_EOF, NULL);  // creates token for EOF
        }

        else if (**input == '&' && (*input)[1] == '&')
        {
            token = create_token(TOKEN_AND, NULL);  // creates token for AND
            *input += 2;
        }

        else if (**input == '|' && (*input)[1] == '|')
        {
            token = create_token(TOKEN_OR, NULL);   // creates token for OR
            *input += 2;
        }

        else
        {
            token = create_token(TOKEN_WORD, readWord(input));  // creates token for WORD
        }

        if (!token) {
            freeTokens(head);
            return NULL;
        }

        addToken(&head, token);     // adding tokens to linked list

        if (token->type == TOKEN_EOF) {     // ends endless loop
            break;
        }
    }

    return head;    // returns first item in list
}

void freeTokens(t_Token *head)   // freeing memory from heap
{
    t_Token *current;
    t_Token *next;

    current = head;

    while (current)             // every element from list gets freed
    {
        next = current->next;
        free(current->value);
        free(current);
        current = next;
    }
}