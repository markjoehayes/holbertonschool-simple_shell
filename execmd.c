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

