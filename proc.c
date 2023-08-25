#include "main.h"
#include <stdlib.h>

/**
 * prompt - displays a prompt
 * @p_name: program name to print on error
 */
void prompt(char *p_name)
{
	int t_stat, status;

	t_stat = isatty(0);
	if (t_stat == 1)
	{
		status = write(1, "($) ", PT_LEN);
		if (status == -1)
		{
			err_handle(p_name);
			exit(98);
		}
	}
}

/**
 * specify - runs builtin commands
 * @cmd: command string to check
 * @env: the environmeent array
 * @arg: the argument array to free
 * @x: exit status
 * @FREE_ARGS: Macro containing parameters to free
 * Return: 0 if not builtin, 1 if builtin, exit on exit
 */
int specify(char *cmd, char **env, FREE_ARGS, int x)
{
	int i;

	if (_strcmp(cmd, "env") == 0)
	{
		for (i = 0; env[i]; i++)
		{
			write(1, env[i], _strlen(env[i]));
			_puts("\n", 1);
		}
		free(arg);
		return (1);
	}
	else if (_strcmp(cmd, "exit") == 0)
	{
		free(arg);
		free(buffer);
		exit(x);
	}

	return (0);
}

/**
 * get_arg - splits the line into arguments
 * @src: char array read by getline()
 * @arr: array of d-alloc strings to contain arguments
 * Return: array of arguments
 */
char **get_arg(char *src, char **arr)
{
	int i, count;
	char *buffer;

	for (i = 0, count = 0; src[i] != '\0'; i++)
		if (src[i] == ' ')
			count++;
	arr = malloc(sizeof(char *) * (count + 2));
	buffer = strtok(src, " ");
	for (i = 0; buffer != NULL; i++)
	{
		arr[i] = buffer;
		buffer = strtok(NULL, " ");
	}
	arr[count + 1] = NULL;
	return (arr);
}

/**
 * p_handl - handles PATH
 * @cmd: address of the cmd to be passed to execve
 * @env: environment variable
 * @prog: name of program
 * @exe: execution line
 * Return: 0 on completion and 1 on failure
 */
int p_handl(char **cmd, char **env, char *prog, char **arg)
{
	char *path, **tmp;

	path = fpath(env);
	if (path == NULL)
	{
		err_handle(prog);
		free(arg);
		return (1);
	}
	tmp = split_path(path);
	*cmd = get_cmd(tmp, arg[0]);
	if (*cmd == NULL)
	{
		err_handle(prog);
		free(arg);
		return (1);
	}
	return (0);
}

/**
 * execute - creates a child process that runs the execution
 * @cmd: address of the cmd to be passed to execve
 * @env: environment variable
 * @prog: name of program
 * @FREE_ARGS: Macro containing parameters to free
 *
 * Return: 0 on execution 2 on error and exits if fork fails
 */

int execute(char *cmd, char **env, char *prog, FREE_ARGS)
{
	int p_stat, e_stat;
	pid_t child;

	p_stat = ispath(arg[0]);
	child = fork();
	if (child == -1)
	{
		err_handle(prog);
		free(arg);
		if (p_stat == 0)
			free(cmd);
		free(buffer);
		exit(98);
	}
	if (child == 0)
	{
		if (execve(cmd, arg, env) == -1)
		{
			err_handle(prog);
			_exit(2);
		}
		_exit(0);
	}
	else
		waitpid(child, &e_stat, 0);
	if (ispath(arg[0]) == 0)
		free(cmd);
	free(arg);
	e_stat =  WEXITSTATUS(e_stat);
	return (e_stat);
}
