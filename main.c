#include "shell.h"
/**
 * main - shell looping
 * Return: 0 for success 
 */
int main(void)
{
    char *buff = NULL;
    size_t buffsize = 0; /* initialize to 0 so getline allocates */
    char **cmd = NULL;

    signal(SIGINT, SIG_N);

    if (isatty(STDIN_FILENO))
        printf("$ ");

    while (getline(&buff, &buffsize, stdin) > 0)
    {
        cmd = split(buff, DELIM);

        if (cmd[0])
        {
            if (strcmp(cmd[0], "env") == 0)
                print_env();
            else
                if_fun(cmd);
        }

        freeArr(cmd);
        cmd = NULL;

        if (isatty(STDIN_FILENO))
            printf("$ ");
    }

    free(buff);
    return (0);
}

