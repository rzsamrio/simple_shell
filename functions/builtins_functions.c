#include "main.h"

/**
 * fbuiltin - builtin that pais the command in the arg
 * @cmd: command
 * 
 * Return: pointer to appropriate function
 */
int (*fbuiltin(char *cmd))(sh_var *)
{
	sh_builtin builtin[] = {
		{ "env", _env },
		{ "exit", fexit },
		{ "setenv", _setenv },
		{ "unsetenv", _unsetenv },
		{"cd", fcd},
		{"help", get_help},
		{ NULL, NULL }
	};
	int i;

	for (i = 0; builtin[i].name; i++)
	{
		if (_strcmp(builtin[i].name, cmd) == 0)
			break;
	}

	return (builtin[i].f);
}

/**
 * envcmp - compares env variables to env var names
 * @nenv: name of the environment variable
 * @name: name passed
 *
 * Return: 0 if are not equal
 * positive value if they are
 */
int envcmp(const char *nenv, const char *name)
{
	int i;

	for (i = 0; nenv[i] != '='; i++)
	{
		if (nenv[i] != name[i])
			return (0);
	}

	return (i + 1);
}


/**
 * _getenv - gets an environment variable
 * @name: name of the env variable
 * @_environ: environment variable
 *
 * Return: value of the environment variable
 * or NULL, if environment variable isn't found
 */
char *_getenv(const char *name, char **_environ)
{
	char *envp = NULL;
	int i, mov = 0;

	for (i = 0; _environ[i]; i++)
	{
		mov = envcmp(_environ[i], name);
		if (mov)
		{
			envp = _environ[i];
			break;
		}
	}

	return (envp + mov);
}

/**
 * new_env - creates new env or alias
 * @name: name
 * @value: value
 *
 * Return: new env or alias.
 */
char *new_env(char *name, char *value)
{
	char *new;
	int len, len1, len2;

	len1 = _strlen(name);
	len2 = _strlen(value);
	len = len1 + len2 + 2;
	new = malloc(sizeof(char) * (len));
	_strcpy(new, name);
	_strcat(new, "=");
	_strcat(new, value);
	_strcat(new, "\0");

	return (new);
}

/**
 * _setenv - compares env variables names
 * @vars: necessary variables
 *
 * Return: 1 if ran successfully
 */
int _setenv(sh_var *vars)
{

	if (vars->args[1] == NULL || vars->args[2] == NULL)
	{
		get_error(vars, -1);
		return (1);
	}

	set_env(vars->args[1], vars->args[2], vars);

	return (1);
}
