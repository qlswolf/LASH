#include <readcommand.h>
#include <Lexer.h>
#include <Parser.h>

int main()
{
    char *input = readCommand();

    t_Token *tokens = lexer(&input);

    t_AST *nodes = parser(tokens);

    printAST(nodes, 0);

    return 0;
}