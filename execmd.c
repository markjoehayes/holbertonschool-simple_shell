#include "shell.h"
/**
 * execmd - function that executes the command stored in cmd[]
 * @cmd: the commande
 */

int execmd(char **cmd)
{
    pid_t pid;
    int status;

    pid = fork();
	/*printf("fork returned: %d\n", pid);*/ 
	fflush(stdout);
    if (pid == 0)
    {
		/*printf("cmd[0] before exec: %s\n", cmd[0]);*/

		/*printf("Child: running [%s]\n", cmd[0]);  DEBUG*/
    	fflush(stdout); /* force flush*/
        if (execve(cmd[0], cmd, environ) == -1)
        {
            perror("execve failed");
            exit(127);
        }
    }
    else if (pid < 0)
    {
        perror("fork failed");
        return 1;
    }
    else
    {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            return WEXITSTATUS(status);
    }

    return 0;
}
/**
 * if_fun - function that tests execution of a different command in cmd[]
 * @cmd: the command
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

