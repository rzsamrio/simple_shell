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
	pid_t pid;
	int check, st = 0;
	char **args = NULL, **tmp = NULL, *cmd = NULL, *clone = NULL;

	clone = malloc(sizeof(char) * (_strlen(line) + 1));
	_strcpy(clone, line);
	args = tokenize(clone);
	cmd = args[0];
	if (ispath(cmd) == 0)
	{
		tmp = spath(environ);
		cmd = fetchc(tmp, cmd);
		st++;
		if (!cmd)
		{
			err_handle(prog, args, tmp, clone);
			return (2);
		}
	}
	
	pid = fork();
	if (pid == -1)
	{
		err_handle(prog, args, tmp, clone);
		return (-1);
	}
	if (pid == 0)
	{
		check = execve(cmd, args, environ);
		if (check == -1)
		{
			err_handle(prog, args, tmp, clone);
			_exit(0);
		}
	}
	else
		waitpid(pid, NULL, 0);
	err_handle(NULL, args, tmp, clone);

	return (st == 1 ? (free(cmd), 0) : 0);
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
	if (!args)
		return (NULL);

	for (i = 0; token; i++)
	{
		args[i] = token;
		token = strtok(NULL, " \n");
	}
	args[argc] = NULL;

	return (args);
}

