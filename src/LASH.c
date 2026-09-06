#include <readline.h>
#include <Lexer.h>

int main() {
    t_Token *tokens;

    char* input = readline();

    tokens = lexer(&input);

    return 0;
}