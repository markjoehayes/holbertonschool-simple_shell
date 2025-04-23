#include "shell.h"
/**
 * if_fun - function that tests execution of a different command in cmd[]
 * @cmd: the commande
 */
void if_fun(char **cmd)
{
	struct stat status;

	if (cmd == NULL)
	{
		exit(EXIT_SUCCESS);
	}
	if (strcmp(cmd[0], "exit") == 0)
	{
		exit(0);
	}
	if (stat(cmd[0], &status) != 0)
		bin(cmd); /** get the path*/
	if (cmd[0] == NULL)
		printf("Command not found\n");
	else
		execmd(cmd);
}
