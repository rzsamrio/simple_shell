#include "main.h"

/**
 * _env - prints the evironment variables
 * @vars: sh_var struct
 *
 * Return: always 1
 */
int _env(sh_var *vars)
{
	int i, j;

	for (i = 0; vars->_environ[i]; i++)
	{

		for (j = 0; vars->_environ[i][j]; j++)

		write(STDOUT_FILENO, vars->_environ[i], j);
		write(STDOUT_FILENO, "\n", 1);
	}

	vars->status = 0;

	return (1);
}

/**
 * set_env - sets an environment variable
 * @name: name of the env variable
 * @value: value of the env variable
 * @vars: sh_var struct
 *
 * Return: void
 */
void set_env(char *name, char *value, sh_var *vars)
{
	int i;
	char *env_var, *env_name;

	for (i = 0; vars->_environ[i]; i++)
	{
		env_var = _strdup(vars->_environ[i]);
		env_name = _strtok(env_var, "=");
		if (_strcmp(env_name, name) == 0)
		{
			free(vars->_environ[i]);
			vars->_environ[i] = new_var(env_name, value);
			free(env_var);
			return;
		}
		free(env_var);
	}

	vars->_environ = _reallocdp(vars->_environ, i, sizeof(char *) * (i + 2));
	vars->_environ[i] = new_var(name, value);
	vars->_environ[i + 1] = NULL;
}

/**
 * _unsetenv - deletes a environment variable
 * @vars: sh_var struct
 *
 * Return: 1 on success.
 */
int _unsetenv(sh_var *vars)
{
	char **realloc_environ;
	char *env_var, *env_name;
	int i, j, k;

	if (vars->args[1] == NULL)
	{
		get_error(vars, -1);
		return (1);
	}
	k = -1;
	for (i = 0; vars->_environ[i]; i++)
	{
		env_var = _strdup(vars->_environ[i]);
		env_name = _strtok(env_var, "=");
		if (_strcmp(env_name, vars->args[1]) == 0)
		{
			k = i;
		}
		free(env_var);
	}
	if (k == -1)
	{
		get_error(vars, -1);
		return (1);
	}
	realloc_environ = malloc(sizeof(char *) * (i));
	for (i = j = 0; vars->_environ[i]; i++)
	{
		if (i != k)
		{
			realloc_environ[j] = vars->_environ[i];
			j++;
		}
	}
	realloc_environ[j] = NULL;
	free(vars->_environ[k]);
	free(vars->_environ);
	vars->_environ = realloc_environ;
	return (1);
}

/**
 * fexit - exits the shell
 * @vars: contains the status and arguments
 *
 * Return: 0 if ran successfuly
 */
int fexit(sh_var *vars)
{
	unsigned int ustatus;
	int ncheck, len;
	int limit;

	if (vars->args[1] != NULL)
	{
		ustatus = _atoi(vars->args[1]);
		ncheck = numcheck(vars->args[1]);
		len = _strlen(vars->args[1]);
		limit = ustatus > (unsigned int)INT_MAX;
		if (!ncheck || len > 10 || limit)
		{
			get_error(vars, 2);
			vars->status = 2;
			return (1);
		}
		vars->status = (ustatus % 256);
	}
	return (0);
}

