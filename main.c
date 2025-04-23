#include "shell.h"
/**
 * main - shell looping
 * Return: 0 for success 
 */

int main(void)
{
	char *buff = NULL;
	size_t buffsize = 1;
	char **cmd;

	buff = malloc(sizeof(char) * buffsize);
	signal(SIGINT, SIG_N);
	if (buff == NULL)
	{
		perror("fault");
		return (EXIT_FAILURE);
	}

	/* Interactive mode if input is from terminal */
    if (isatty(STDIN_FILENO))
		printf("$ ");

	while (getline(&buff, &buffsize, stdin) > 0)
	{
    	cmd = split(buff, DELIM);
		if (cmd[0] != NULL)
		{
    		if (strcmp(cmd[0], "env") == 0)
        		print_env();
    		else
 				if_fun(cmd);
    	}

    freeArr(cmd);

    /* Reprint prompt in interactive mode */
    if (isatty(STDIN_FILENO))
        printf("$ ");
	}
	
	free(buff);
	exit(EXIT_SUCCESS);
	return (0);
}
