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
	char *cmd, **arg, *buffer;
	int rc;
	const int t_stat = isatty(0);

	while (1)
	{
		prompt(av[0]);
		buffer = exe_read(av[0], &rc);
		if (rc == 0)
			break;
		else if (rc == 1)
			continue;
		arg = get_arg(buffer, arg);
		if (specify(arg[0], environ) == 1)
		{
			free(buffer);
			continue;
		}

		if (ispath(arg[0]) == 0)
		{
			if (p_handl(&cmd, environ, av[0], arg) == 1)
			{
				if (t_stat == 0)
					break;
				free(buffer);
				continue;
			}
		}
		else
			cmd = arg[0];

		execute(cmd, environ, av[0], arg, buffer);
		if (t_stat == 0)
			break;
		free(buffer);
	}
	free(buffer);
	return (0);
}
