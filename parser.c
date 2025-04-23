#include "shell.h"


char *get_path_value(void)
{
    int i = 0;
    char *key = "PATH=";
    size_t len = strlen(key);

    while (environ[i])
    {
        if (strncmp(environ[i], key, len) == 0)
            return environ[i] + len; /* return value after "PATH="*/
        i++;
    }
    return NULL;
}



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
    size_t size;
    char *path_val = get_path_value();

    path = path_val ? strdup(path_val) : strdup(MYPATH);
    if (!path)
    {
        perror("strdup failed");
        freeArr(cmd);
        exit(EXIT_FAILURE);
    }

    if ((path_val == NULL || path_val[0] == '\0') &&
        cmd[0][0] != '/' && strncmp(cmd[0], "./", 2) != 0)
    {
        write(STDERR_FILENO, "./hsh: 1: ", 10);
        write(STDERR_FILENO, cmd[0], strlen(cmd[0]));
        write(STDERR_FILENO, ": not found\n", 12);
        free(path);
        freeArr(cmd);
        exit(127);
    }

    tok = split(path, ":"); /* Assuming you have a split() for colon*/
    if (!tok)
    {
        free(path);
        freeArr(cmd);
        exit(EXIT_FAILURE);
    }

    for (i = 0; tok[i]; i++)
    {
        size = strlen(tok[i]) + strlen(cmd[0]) + 2;
        bin = malloc(size);
        if (!bin)
        {
            perror("malloc");
            freeArr(tok);
            free(path);
            freeArr(cmd);
            exit(EXIT_FAILURE);
        }

        snprintf(bin, size, "%s/%s", tok[i], cmd[0]);

        if (access(bin, X_OK) == 0)
        {
            free(cmd[0]);
            cmd[0] = strdup(bin); /* Replace command with full path*/
            free(bin);
            freeArr(tok);
            free(path);
            return;
        }

        free(bin);
        bin = NULL;
    }

    /* If no path worked:*/
    write(STDERR_FILENO, "./hsh: 1: ", 10);
    write(STDERR_FILENO, cmd[0], strlen(cmd[0]));
    write(STDERR_FILENO, ": not found\n", 12);

    freeArr(tok);
    free(path);
    freeArr(cmd);
    exit(127);
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
    char **cmd = malloc(sizeof(char *) * MAX_TOKENS);
    size_t idx = 0;


    if (!cmd)
    {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }

    ptr = strtok(buff, limit);
    while (ptr && idx < MAX_TOKENS - 1)
    {
        cmd[idx] = strdup(ptr);
        if (!cmd[idx])
        {
            perror("strdup failed");
            exit(EXIT_FAILURE);
        }
        ptr = strtok(NULL, limit);
        idx++;
    }


    cmd[idx] = NULL;
    return cmd;
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
	
	if (!array)
		return;
	for (i = 0; array[i]; i++)
	{
		free(array[i]);
	}
	free(array);
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
