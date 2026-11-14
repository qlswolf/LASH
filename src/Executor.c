#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#include "Parser.h"
#include "Executor.h"

static int executeBuiltins(t_AST *node)
{
    if (strcmp(node->words->value, "exit") == 0)
    {
        printf("exit\n");
        exit(0);
    }

    return -1;
}

static int executeCommand(t_AST *node)
{
    t_Wordcommand *word;
    char **argv;
    int argc;
    int i;
    pid_t pid;
    int status;

    argc = 0;
    word = node->words;
    while (word)
    {
        argc++;
        word = word->next;
    }

    argv = malloc(sizeof(char *) * (argc + 1));
    if (!argv)
    {
        return 1;
    }

    word = node->words;
    i = 0;
    while (word)
    {
        argv[i] = word->value;
        i++;
        word = word->next;
    }
    argv[i] = NULL;

    i = 0;

    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        free(argv);
        return 1;
    }

    if (pid == 0)
    {
        execvp(argv[0], argv);

        perror("execvp failed");
        _exit(127);
    }

    while (waitpid(pid, &status, 0) < 0)
    {
        if (errno != EINTR)
        {
            perror("waitpid");
            free(argv);
            return 1;
        }
    }

    free(argv);

    if (WIFEXITED(status))
    {
        return (WEXITSTATUS(status));
    }
    if (WIFSIGNALED(status))
    {
        return (128 + WTERMSIG(status));
    }

    return 1;
}

int executor(t_AST *node)
{
    int status;

    if (!node)
    {
        return 1;
    }

    if (node->type == AST_COMMAND)
    {
        status = executeBuiltins(node);

        if (status != -1)
        {
            return status;
        }

        return (executeCommand(node));
    }

    if (node->type == AST_AND)
    {
        status = executor(node->left);

        if (status == 0)
        {
            return (executor(node->right));
        }

        return status;
    }

    if (node->type == AST_OR)
    {
        status = executor(node->left);

        if (status != 0)
        {
            return (executor(node->right));
        }

        return status;
    }

    return 1;
}