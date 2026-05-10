#include <stdio.h>
#include "Lexer.h"

static t_Token *create_token(t_TokenType type, char *value) {
    t_Token *token = malloc(sizeof(t_Token));
    if (!token) {
        printf("Error: Memory allocation for token failed.\n");
        return NULL;
    }
    token->type = type;
    token->value = value;
    return token;
}

static char *read_word(char **input) {
    char *buf = *input;
    while (**input && **input != ' ' && **input != '|' && **input != '"' && **input != "<" && **input != ">") {
        (*input)++;
    }
    return buf;
} 

static t_Token *read_redirect(char **input) {
    char *buf = *input;
    t_TokenType type;

    if (**input == '>') {
        type = REDIRECT_OUT;
    } else if (**input == '<') {
        type = REDIRECT_IN;
    } else {
        return NULL;
    }
    (*input)++;
    return create_token(type, buf);
}

t_Token *lexer(char *input) {
    t_Token *head = NULL;
    t_Token *current = NULL;

    while (*input) {
        while (*input == ' ') {
            input++;
        }
        if (*input == '\0') {
            break;
        }
        if (*input == '|') {
            t_Token *token = create_token(PIPE, "|");
            if (!head) {
                head = token;
                current = head;
            }
            else {
                current->next = token;
                current = current->next;
            }
        }
        else if (*input == '>' || *input == '<') {
            t_Token *token = read_redirect(&input);
            if (!head) {
                head = token;
                current = head;
            }
            else {
                current->next = token;
                current = current->next;
            }
        }
        else {
            char *word = read_word(&input);
            t_Token *token = create_token(WORD, word);
            if (!head) {
                head = token;
                current = head;
            }
            else {
                current->next = token;
                current = current->next;
            }
        }
    }
    return head;
}

void free_tokens(t_Token *head) {
    t_Token *current = head;
    while (current) {
        t_Token *next = current->next;
        free(current);
        current = next;
    }
}