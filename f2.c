#include "main.h"

/**
 * fcall - calls a process based on user's input
 * @line: the user's input
 * @prog: the name of the program
 *
 * Return: 0 on success
 * or,     1 on new line input
 * or,    -1 on fork() failure
*/
int fcall(char *line, char *prog)
{
	pid_t pid; int st = 1; 
	char **args, **tmp, *cmd;

	if (line[0] == '\n')
		return (1);

	args = tokenize(line);
	if (runc(args[0], environ) == 1)
		return (1);
	cmd = args[0];

	if (ispath(cmd) == 0)
	{
		st = 0;
		tmp = spath(environ);
		cmd = fetchc(tmp, cmd);
		if (!cmd)
		{
			err_handle(prog);
			free(args);
			return (2);
		}
	}

	if ((pid = fork()) == -1)
	{
		err_handle(prog);
		free(args);
		free(line);
		return (-1);
	}

	if (pid == 0)
	{
		if (execve(cmd, args, environ) == -1)
		{
			err_handle(prog);
			free(args);
			free(line);
			_exit(0);
		}
	}
	else
		waitpid(pid, NULL, 0);

	free(args);
	if (st == 0)
		free(cmd);

	return (0);
}

	/**
	 * tokenize - turns a line input into an array of strings/arguments
	 * @line: the user's input line
	 *
	 * Return: array of strings/arguments
	*/
char **tokenize(char *line)
{
	char **args = NULL, *token;
	int argc = 1, i;

	for (i = 0; line[i] != '\0'; i++)
		if (line[i] == ' ')
			argc++;

	token = strtok(line, " \n");
	args = malloc((argc + 1) * sizeof(char *));
	if (!args) return (NULL);

	for (i = 0; token; i++)
	{
		args[i] = token;
		token = strtok(NULL, " \n");
	}
	args[argc] = NULL;

	return (args);
}

/**
 * runc - runs builtin commands
 * @cmd: command string to check
 * env: the environmeent string
 * Return: 0 if not builtin, 1 if builtin, exit on exit
 */
int runc(char *cmd, char **env)
{
	int i;

	if (_strcmp(cmd, "env/") == 0)
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
	
