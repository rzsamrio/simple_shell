#include "main.h"

/**
 * ispath - checks whether a command isn't a path
 * @cmd: the command 
 * 
 * Return: 0 -> not a path
 * ------- 1 -> not a command (could be a path to the command)
*/
int ispath(char *cmd)
{
	int i;

	for(i = 0; cmd[i] != '\0'; i++)
		if (cmd[i] == '/')
			return (1); /* not a command, could be a path */

	return (0); /* definitely not a path*/
}

char *fpath(char **env)
{
	char *pathv;
	int i;

	for (i = 0; env[i]; i++)
	{
		if (_strncmp(env[i], "PATH=", 5) == 0)
		{
			pathv = malloc(sizeof(char) * (_strlen(env[i]) - 4));
			if (!pathv) return (NULL);

			_strcpy(pathv, env[i] + 5);
			return (pathv);
		}
	}

	return (NULL);
}

char **spath(char **env)
{
	int i, count;
	char *token, **dir;
	char *path = fpath(env);

	for (i = 0, count = 1; path[i]; i++)
		if (path[i] == ':')
			count++;

	dir = malloc(sizeof(char *) * (count + 1));
	if (!dir) return (NULL);

	token = strtok(path, ":");
	for (i = 0; token; i++)
	{
		dir[i] = token;
		token = strtok(NULL, ":");
	}
	free(path);
	return (dir);
}

char *fetchc(char **path, char *cmd)
{
	int i, status;
	char *loc;
	struct stat file;

	for (i = 0; path[i]; i++)
	{
		loc = _strcat(path[i], cmd);
		status = stat(loc, &file);
		if (status == 0)
		{
			free(path);
			return (loc);
		}
		free(loc);
	}
	free(path);
	return (NULL);
}
