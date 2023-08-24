#include "main.h"

/**
 * clone_arr - clones an array of strings
 * @array: array of strings
 * Return: d-alloc clone of passed array
 */
char **clone_arr(char **array)
{
	int i, size;
	char **clone;

	for (i = 0; array[i] != NULL; i++);
	clone = malloc(sizeof(char *) * (i + 1));
	for (i = 0; array[i] != NULL; i++)
	{
		size = _strlen(array[i]);
		clone[i] = malloc(size + 1);
		clone[i] = _strcpy(clone[i], array[i]);
	}
	clone[i] = NULL;
	return (clone);
}

/**
 * get_var - finds and returns the Requested variable
 * @var: requested variable to serch for
 * @env: sacrificial environment string
 *
 */

char *get_var(char **env, char *var)
{
	int i, size;
	char *buffer, *tmp;

	for (i = 0; env[i] != NULL; i++)
	{
		buffer = strtok(env[i], "=");
		if (_strcmp(buffer, var) == 0)
		{
			buffer = strtok(NULL, "=");
			size = _strlen(buffer);
			tmp = malloc(size + 1);
			tmp = _strcpy(tmp, buffer);
			free_array(env);
			return (tmp);
		}
	}
	return (NULL);
}

/**
 * fpath: Finds the PATH value in the environment
 * @env: environment variable
 * Return: PATH or NULL if not found
 */
char *fpath(char *env[])
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
 * split_path - saves the PATH into an array
 * @path: PATH
 * Return: PATH array
 */
char **split_path(char *path)
{
	int i, num;
	char *buffer, **parr;

	for (i = 0, num = 0; path[i]; i++)
		if (path[i] == ':')
			num++;
	parr = malloc(sizeof(char *) * (num + 2));
	buffer = strtok(path, ":");
	for (i = 0; buffer != NULL; i++)
	{
		parr[i] = malloc(sizeof(char) * _strlen(buffer));
		parr[i] = _strcpy(parr[i], buffer);
		buffer = strtok(NULL, ":");
	}
	parr[num + 1] = NULL;
	free(path);
	return (parr);
}

/**
 * get_cmd - retrieves the execution path if it exists
 * @path_array: array containing PATH elements
 * @cmd: execution command
 * Return: execution path
 */
char *get_cmd(char *path_array[], char *cmd)
{
	int i, status;
	char *tmp;
	struct stat file;

	for (i = 0; path_array[i] != NULL; i++)
	{
		tmp = _strcat(path_array[i], cmd);
		status = stat(tmp, &file);
		if (status == 0)
		{
			free_array(path_array);
			return (tmp);
		}
		free(tmp);
	}
	free_array(path_array);
	return (NULL);
}

