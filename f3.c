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

	for (i = 0; cmd[i] != '\0'; i++)
		if (cmd[i] == '/')
			return (1); /* not a command, could be a path */

	return (0); /* definitely not a path*/
}

/**
 * fpath - finds the value of the PATH environment variable
 * @env: the environment variables
 *
 * Return: the value of PATH
*/
char *fpath(char **env)
{
	char *pathv;
	int i;

	for (i = 0; env[i]; i++)
	{
		if (_strncmp(env[i], "PATH=", 5) == 0)
		{
			pathv = malloc(sizeof(char) * (_strlen(env[i]) - 4));
			if (!pathv)
				return (NULL);

			_strcpy(pathv, env[i] + 5);
			return (pathv);
		}
	}

	return (NULL);
}

/**
 * spath - splits PATH into directories
 * @env: environment variables
 *
 * Return: array of each directory
*/
char **spath(char **env)
{
	int i, count;
	char *token = NULL, **dir = NULL;
	char *path = fpath(env);

	for (i = 0, count = 1; path[i]; i++)
		if (path[i] == ':')
			count++;

	dir = malloc(sizeof(char *) * (count + 1));
	if (!dir)
		return (NULL);

	token = strtok(path, ":");
	for (i = 0; token; i++)
	{
		dir[i] = token;
		token = strtok(NULL, ":");
	}

	free(path);

	return (dir);
}

/**
 * fetchc - search for the cmd in PATH
 * @path: the directories to check
 * @cmd: the command to look for
 *
 * Return: the path to the command if found
 * else, returns NULL
*/
char *fetchc(char **path, char *cmd)
{
	int i, status;
	char *loc = NULL;
	struct stat file;

	for (i = 0; path[i]; i++)
	{
		loc = _strcat(path[i], cmd);
		status = stat(loc, &file);
		if (status == 0)
			return (loc);

		free(loc);
	}

	return (NULL);
}

/**
 * _strcat - concatenates path to cmd
 * @s1: the path
 * @s2: the command
 *
 * Return: the concatenated string
*/
char *_strcat(char *s1, char *s2)
{
	char *str = NULL;
	int i, j;

	str = malloc(_strlen(s1) + _strlen(s2) + 2);

	for (i = 0; s1[i]; i++)
		str[i] = s1[i];

	str[i] = '/';
	i++;

	for (j = 0; s2[j]; i++, j++)
		str[i] = s2[j];

	str[i] = '\0';

	return (str);
}
