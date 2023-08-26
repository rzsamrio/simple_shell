#include "main.h"

/**
 * is_cdir - checks for ':' in the cwd
 * @path: path
 * @i: index
 *
 * Return: 1 if the path can be searched in the cd
 * 0 if not
 */
int is_cdir(char *path, int *i)
{
	if (path[*i] == ':')
		return (1);

	while (path[*i] != ':' && path[*i])
	{
		*i += 1;
	}

	if (path[*i])
		*i += 1;

	return (0);
}

/**
 * _which - command locator
 * @cmd: the command
 * @_environ: environment variable
 *
 * Return: command location
 */
char *_which(char *cmd, char **_environ)
{
	char *path, *ptr_path, *token_path, *dir;
	int len_dir, len_cmd, i;
	struct stat st;

	path = _getenv("PATH", _environ);
	if (path)
	{
		ptr_path = _strdup(path);
		len_cmd = _strlen(cmd);
		token_path = _strtok(ptr_path, ":");
		i = 0;
		while (token_path != NULL)
		{
			if (is_cdir(path, &i))
				if (stat(cmd, &st) == 0)
					return (cmd);
			len_dir = _strlen(token_path);
			dir = malloc(len_dir + len_cmd + 2);
			_strcpy(dir, token_path);
			_strcat(dir, "/");
			_strcat(dir, cmd);
			_strcat(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(ptr_path);
				return (dir);
			}
			free(dir);
			token_path = _strtok(NULL, ":");
		}
		free(ptr_path);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}

/**
 * is_executable - determines if cmd is an executable
 * @vars: sh_var struct
 *
 * Return: 0, cmd -> not an executable
 * other num, cmd -> is an executable 
 */
int is_executable(sh_var *vars)
{
	struct stat st;
	int i;
	char *input;

	input = vars->args[0];
	for (i = 0; input[i]; i++)
	{
		if (input[i] == '.')
		{
			if (input[i + 1] == '.')
				return (0);
			if (input[i + 1] == '/')
				continue;
			else
				break;
		}
		else if (input[i] == '/' && i != 0)
		{
			if (input[i + 1] == '.')
				continue;
			i++;
			break;
		}
		else
			break;
	}
	if (i == 0)
		return (0);

	if (stat(input + i, &st) == 0)
	{
		return (i);
	}
	get_error(vars, 127);
	return (-1);
}

/**
 * check_perm - checks user's access permission
 * @dir: destination directory
 * @vars: sh_var struct
 *
 * Return: 0 -> no errors
 * 1 -> errors occurred
 */
int check_perm(char *dir, sh_var *vars)
{
	if (dir == NULL)
	{
		get_error(vars, 127);
		return (1);
	}

	if (_strcmp(vars->args[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			get_error(vars, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(vars->args[0], X_OK) == -1)
		{
			get_error(vars, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * cmd_exec - executes command lines
 * @vars: sh_var struct
 *
 * Return: 1 if ran successfuly
 */
int cmd_exec(sh_var *vars)
{
	pid_t id;
	pid_t wid;
	int state;
	int exec;
	char *dir;
	(void) wid;

	exec = is_executable(vars);
	if (exec == -1)
		return (1);
	if (exec == 0)
	{
		dir = _which(vars->args[0], vars->_environ);
		if (check_perm(dir, vars) == 1)
			return (1);
	}

	id = fork();
	if (id == 0)
	{
		if (exec == 0)
			dir = _which(vars->args[0], vars->_environ);
		else
			dir = vars->args[0];
		execve(dir + exec, vars->args, vars->_environ);
	}
	else if (id < 0)
	{
		perror(vars->av[0]);
		return (1);
	}
	else
	{
		do {
			wid = waitpid(id, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}

	vars->status = state / 256;
	return (1);
}
