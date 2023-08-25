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
	char *cmd, **arg, *buffer, *exe, *ptr;
	int rc,  e_status = 0;
	const int t_stat = isatty(0);

	while (1)
	{
		prompt(av[0]);
		buffer = exe_read(av[0], &rc);
		if (rc == 0)
			break;
		else if (rc == 1)
			continue;
		
		ptr = buffer; /* dummy init */
		exe = _strtokr(buffer, "\n", &ptr);
		while (exe != NULL)
		{
			arg = get_arg(exe, arg);
			if (specify(arg[0], environ, arg, buffer, e_status) == 1)
				continue;
			if (ispath(arg[0]) == 0)
			{
				if (p_handl(&cmd, environ, av[0], arg) == 1)
					continue;
			}
			else
				cmd = arg[0];
			e_status = execute(cmd, environ, av[0], arg, buffer); 
			exe = _strtokr(NULL, "\n", &ptr);
		}
		if (t_stat == 0)
			break;
		free(buffer);
	}
	free(buffer);
	return (e_status);
}
