#include "main.h"

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
 * Return: 0 if not builtin, 1 if builtin, exit on exit
 */
int specify(char *cmd, char **env)
{
	int i;

	if (_strcmp(cmd, "env") == 0)
	{
		for (i = 0; env[i]; i++)
		{
			write(1, env[i], _strlen(env[i]));
			_puts("\n", 1);
		}
		return (1);
	}
	else if (_strcmp(cmd, "exit") == 0)
		exit(0);

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
int p_handl(char **cmd, char **env, char *prog, char **exe)
{
	char *path, **tmp;

	path = fpath(env);
	if (path == NULL)
	{
		err_handle(prog);
		free(exe);
		return (1);
	}
	tmp = split_path(path);
	*cmd = get_cmd(tmp, exe[0]);
	if (*cmd == NULL)
	{
		err_handle(prog);
		free(exe);
		return (1);
	}
	return (0);
}

/**
 * execute - creates a child process that runs the execution
 * @cmd: address of the cmd to be passed to execve
 * @env: environment variable
 * @prog: name of program
 * @exe: execution line
 * @buffer: string holding getline content
 * Return: 0 on completion and exits on failure
 */

int execute(char *cmd, char **env, char *prog, char **exe, char *buffer)
{
	int p_stat;
	pid_t child;

	p_stat = ispath(exe[0]);
	child = fork();
	if (child == -1)
	{
		err_handle(prog);
		free(exe);
		if (p_stat == 0)
			free(cmd);
		free(buffer);
		return (1);
	}
	if (child == 0)
	{
		if (execve(cmd, exe, env) == -1)
		{
			err_handle(prog);
			_exit(1);
		}
		_exit(0);
	}
	else
		waitpid(child, NULL, 0);
	if (ispath(exe[0]) == 0)
		free(cmd);
	free(exe);
	return (0);
}
