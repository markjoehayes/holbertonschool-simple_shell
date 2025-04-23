#include "shell.h"
/**
 * if_fun - function that tests execution of a different command in cmd[]
 * @cmd: the commande
 */

int if_fun(char **cmd, int *last_status)
{
    struct stat status;

    if (cmd == NULL)
        return (0);

    if (strcmp(cmd[0], "exit") == 0)
        return (-1);

    if (stat(cmd[0], &status) != 0)
    {
        bin(cmd);  
        if (stat(cmd[0], &status) != 0)
        {
            *last_status = 127;
            fprintf(stderr, "./hsh: command not found: %s\n", cmd[0]);
            return (0);
        }
    }

    *last_status = execmd(cmd);
    return (0);
}

