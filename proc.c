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
 *
 * @FREE_ARGS: Macro containing parameters to free
 * (arg, buffer)
 * @EXEC: Contains the parameters for updating the
 * execution line (exe, ptr)
 * @INTS: Line number and status parameters (x, line)
 *
 * Return: 0 if not builtin, 1 if builtin, exit on exit
 */
int specify(char *cmd, char **env, INTS, FREE_ARGS, EXEC)
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
		*exe = _strtokr(NULL, "\n", ptr);
		(*line)++;
		return (1);
	}
	else if (_strcmp(cmd, "exit") == 0)
	{
		free(arg);
		free(buffer);
		exit(*x);
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
 * @arg: execution line
 *
 * (arg, buffer)
 * @EXEC: Contains the parameters for updating the
 * execution line (exe, ptr)
 * @INTS: Line number and status parameters (x, line)
 *
 * Return: 0 on completion and 1 on failure
 */
int p_handl(char **cmd, char **env, char *prog, char **arg, INTS, EXEC)
{
	char *path, **tmp, *msg;
	struct stat file;

	path = fpath(env);
	if (path == NULL)
	{
		err_handle(prog);
		free(arg);
		*exe = _strtokr(NULL, "\n", ptr);
		(*line)++;
		return (1);
	}
	if (path[0] == '\0')
	{
		free(path);
		path = NULL;
		*cmd = arg[0];
	}

	tmp = split_path(path);
	*cmd = get_cmd(tmp, arg[0]);
	if (stat(*cmd, &file) != 0)
	{
		*exe = _strtokr(NULL, "\n", ptr);
		msg = nocmd(prog, *line, arg[0], "not found\n");
		_puts(msg, 2);
		free(arg);
		free(msg);
		*x = 127;
		(*line)++;
		return (-1);
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
	if (p_stat == 0)
		free(cmd);
	free(arg);
	e_stat =  WEXITSTATUS(e_stat);
	return (e_stat);
}
