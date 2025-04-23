#include "shell.h"
/**
 * bin- search for the command in environment "PATH"
 * @cmd: the commande
 */
void bin(char **cmd)
{
	int i;
	char *path = NULL;
	char *bin = NULL;
	char **tok = NULL;

	path = strdup(getenv("PATH"));
	if (path == NULL)
		path = strdup(MYPATH);
	if (cmd[0][0] != '/' && strncmp(cmd[0], "./", 2) != 0)
	{
		tok = split(path, ":");
		free(path);
		path = NULL;
		for (i = 0; tok[i]; i++)
		{
			bin = calloc(sizeof(char), (strlen(tok[i]) + 2 + strlen(cmd[0])));
			if (bin == NULL)
				break;
			strcat(bin, tok[i]);
			strcat(bin, "/");
			strcat(bin, cmd[0]);
			if (access(bin, F_OK) == 0)
				break;
			free(bin);
			bin = NULL;
		}
		freeArr(tok);
		free(cmd[0]);
		cmd[0] = bin;
	}
	else
	{
		free(path);
		path = NULL;
	}
}

/**
 * split - function taht split the input in an array of string
 * @buff: the input
 * @limit: the delimenter
 * Return: array of string
 */
char **split(char *buff, char *limit)
{
	char *ptr = NULL;
	char **cmd = NULL;
	size_t idx = 0;

	ptr = strtok(buff, limit);
	if (!ptr)
	{
		free(buff);
		exit(EXIT_FAILURE);
	}
	while (ptr)
	{
		cmd = realloc(cmd, ((idx + 1) * sizeof(char *)));
		cmd[idx] = strdup(ptr);
		ptr = strtok(NULL, limit);
		++idx;
	}
	cmd = realloc(cmd, ((idx + 1) * sizeof(char *)));
	cmd[idx] = NULL;
	return (cmd);
}
/**
 * print_env - print envirement
 */
void print_env(void)
{
	size_t c;
	int len;

	for (c = 0; environ[c] != NULL; c++)
	{
		len = strlen(environ[c]);
		write(1, environ[c], len);
		write(STDOUT_FILENO, "\n", 1);
	}
}
/**
 * freeArr - function free
 * @array: : argument needs free
 */
void freeArr(char **array)
{
	int i;

	for (i = 0; array[i]; i++)
	{
		free(array[i]);
		array[i] = NULL;
	}
	free(array);
	array = NULL;
}
/**
 * SIG_N - function signal handler
 * @signal  : input
 */
void SIG_N(int signal)
{
	if (signal == SIGINT)
	{
		putchar('\n');
		write(STDOUT_FILENO, "$ ", 2);
	}
}
