#include "main.h"
#include <stdio.h>

/**
 * main - simple shell
 * @av: cla
 * @ac: number of cla
 * Return: 0
 */
int main(int ac __attribute__((unused)), char **av)
{
	char *cmd, **arg, *buffer, **exe;
	int rc, i, e_status = 0;
	const int t_stat = isatty(0);

	while (1)
	{
		prompt(av[0]);
		buffer = exe_read(av[0], &rc);
		if (rc == 0)
			break;
		else if (rc == 1)
			continue;

		exe = split_exe(buffer);
		for (i = 0; exe[i]; i++)
		{
			arg = get_arg(exe[i], arg);
			if (specify(arg[0], environ, arg, exe, buffer, e_status) == 1)
				continue;
			if (ispath(arg[0]) == 0)
			{
				if (p_handl(&cmd, environ, av[0], arg) == 1)
					continue;
			}
			else
				cmd = arg[0];
			e_status = execute(cmd, environ, av[0], arg, buffer);
			if (e_status == 1)
			{
				free(exe);
				exit(98);
			}
		}
		if (t_stat == 0)
			break;
		free(exe);
		free(buffer);
	}
	free(buffer);
	return (e_status);
}

/*
 *  when ready add this on line 28
 * continue;
 */

