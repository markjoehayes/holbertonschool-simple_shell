#ifndef _SHELL_H_
#define _SHELL_H_

extern char **environ;

#define MAX_TOKENS 100
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#define RL_BUFF_SIZE 1024
#define TK_BUFF_SIZE 64
#define TOK_DELIM " \t\r\n\a"
#define MYPATH "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/snap/bin:"

#include <linux/limits.h>
#define PRINTER(c) (isatty(STDIN_FILENO), write(STDOUT_FILENO, c, strlen(c)))
#define DELIM " \t\r\n\a"
char **split(char *raw_cmd, char *limit);
char **split_line(char *line, char *limit);
void SIG_N(int signal);
void bin(char **cmd);
void print_env(void);
int execmd(char **cmd);
int if_fun(char **cmd, int *last_status);
void freeArr(char **parsedStr);
char *get_path_value(void);

#endif
