#include <stdio.h>

#include "readcommand.h"
#include "Lexer.h"
#include "Parser.h"
#include "Executor.h"

int main()
{
    printf("Welcome to LASH experimental.\n\n");

    do
    {
        printf("<-- LASH --> $ ");
        char *input = readCommand();

        t_Token *tokens = lexer(&input);

        t_AST *AST = parser(tokens);

        if (AST)
        {
            executor(AST);
            freeAST(AST);
        }
    } while (1);
    
}