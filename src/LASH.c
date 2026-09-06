#include <stdio.h>
#include <readcommand.h>
#include <Lexer.h>

void printTokens(t_Token *tokens); // test-function for lexer

int main()
{
    t_Token *tokens;

    char *input = readCommand();

    tokens = lexer(&input);

    printTokens(tokens);

    return 0;
}

void printTokens(t_Token *tokens)
{

    t_Token *current;
    t_Token *next;

    current = tokens;

    while (current)
    {
        next = current->next;

        if (current->type == TOKEN_AND)
        {
            printf("AND\n");
        }
        else if (current->type == TOKEN_OR)
        {
            printf("OR\n");
        }
        else if (current->type == TOKEN_WORD)
        {
            printf("WORD: %s\n", current->value);
        }
        else if (current->type == TOKEN_EOF)
        {
            printf("EOF\n");
        }

        current = next;
    }
}