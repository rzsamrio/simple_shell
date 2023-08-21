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

    if (line[0] == '\0')
    {
        return (1);
    }

	args = tokenize(line);
    cmd = args[0];
    
    if (ispath(cmd) == 0)
    {
        tmp = spath(environ);
        cmd = fetchc(tmp, cmd);
        if (!cmd)
        {
            st = 0;
            err_handle(prog);
            free(args);
            free(tmp);
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
