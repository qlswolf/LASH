#include "readcommand.h"
#include "Lexer.h"
#include "Parser.h"
#include "Executor.h"

int main()
{
    char *input = readCommand();

    t_Token *tokens = lexer(&input);

    t_AST *AST = parser(tokens);

    if (AST)
    {
        executor(AST);
        freeAST(AST);
    }

    return 0;
}