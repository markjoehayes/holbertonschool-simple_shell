#include "shell.h"
/**
 * execmd - function that executes the command stored in cmd[]
 * @cmd: the commande
 */
void execmd(char **cmd)
{

	int val;
	int status = 0;
	pid_t pid = 0;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
	}
	if (pid == 0)
	{

		val = execve(cmd[0], cmd, environ);
		if (val == -1)
			perror("Error:555");
	}
	if (pid > 0)
	{
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	}
}
