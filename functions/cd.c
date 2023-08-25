#include "main.h"

/**
 * cd_shell - change working directory
 * @vars: sh_var struct
 *
 * Return: 1 on success
 */
int cd_shell(sh_var *vars)
{
	char *dir;
	int ishome, ishome2, isddash;

	dir = vars->args[1];

	if (dir != NULL)
	{
		ishome = _strcmp("$HOME", dir);
		ishome2 = _strcmp("~", dir);
		isddash = _strcmp("--", dir);
	}

	if (dir == NULL || !ishome || !ishome2 || !isddash)
	{
		cd_to_home(vars);
		return (1);
	}

	if (_strcmp("-", dir) == 0)
	{
		cd_previous(vars);
		return (1);
	}

	if (_strcmp(".", dir) == 0 || _strcmp("..", dir) == 0)
	{
		cd_dot(vars);
		return (1);
	}

	cd_to(vars);

	return (1);
}

/**
 * cd_dot - changes to the parent directory
 * @vars: sh_var struct
 *
 * Return: void
 */
void cd_dot(sh_var *vars)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_strtok_pwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);
	set_env("OLDPWD", cp_pwd, vars);
	dir = vars->args[1];
	if (_strcmp(".", dir) == 0)
	{
		set_env("PWD", cp_pwd, vars);
		free(cp_pwd);
		return;
	}
	if (_strcmp("/", cp_pwd) == 0)
	{
		free(cp_pwd);
		return;
	}
	cp_strtok_pwd = cp_pwd;
	reverse_string(cp_strtok_pwd);
	cp_strtok_pwd = _strtok(cp_strtok_pwd, "/");
	if (cp_strtok_pwd != NULL)
	{
		cp_strtok_pwd = _strtok(NULL, "\0");

		if (cp_strtok_pwd != NULL)
			reverse_string(cp_strtok_pwd);
	}
	if (cp_strtok_pwd != NULL)
	{
		chdir(cp_strtok_pwd);
		set_env("PWD", cp_strtok_pwd, vars);
	}
	else
	{
		chdir("/");
		set_env("PWD", "/", vars);
	}
	vars->status = 0;
	free(cp_pwd);
}

/**
 * cd_to - changes to a given directory
 * @vars: sh_var struct
 *
 * Return: void
 */
void cd_to(sh_var *vars)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_dir;

	getcwd(pwd, sizeof(pwd));

	dir = vars->args[1];
	if (chdir(dir) == -1)
	{
		get_error(vars, 2);
		return;
	}

	cp_pwd = _strdup(pwd);
	set_env("OLDPWD", cp_pwd, vars);

	cp_dir = _strdup(dir);
	set_env("PWD", cp_dir, vars);

	free(cp_pwd);
	free(cp_dir);

	vars->status = 0;

	chdir(dir);
}

/**
 * cd_previous - changes to the previous working directory
 * @vars: sh_var
 *
 * Return: void
 */
void cd_previous(sh_var *vars)
{
	char pwd[PATH_MAX];
	char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);

	p_oldpwd = _getenv("OLDPWD", vars->_environ);

	if (p_oldpwd == NULL)
		cp_oldpwd = cp_pwd;
	else
		cp_oldpwd = _strdup(p_oldpwd);

	set_env("OLDPWD", cp_pwd, vars);

	if (chdir(cp_oldpwd) == -1)
		set_env("PWD", cp_pwd, vars);
	else
		set_env("PWD", cp_oldpwd, vars);

	p_pwd = _getenv("PWD", vars->_environ);

	write(STDOUT_FILENO, p_pwd, _strlen(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_pwd);
	if (p_oldpwd)
		free(cp_oldpwd);

	vars->status = 0;

	chdir(p_pwd);
}

/**
 * cd_to_home - changes to the home directory
 * @vars: sh_var struct
 *
 * Return: void
 */
void cd_to_home(sh_var *vars)
{
	char *p_pwd, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_pwd = _strdup(pwd);

	home = _getenv("HOME", vars->_environ);

	if (home == NULL)
	{
		set_env("OLDPWD", p_pwd, vars);
		free(p_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		get_error(vars, 2);
		free(p_pwd);
		return;
	}

	set_env("OLDPWD", p_pwd, vars);
	set_env("PWD", home, vars);
	free(p_pwd);
	vars->status = 0;
}
