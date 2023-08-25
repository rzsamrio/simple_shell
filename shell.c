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
	char *cmd, **arg, *buffer, *exe, **tmp;
	int rc, e_status = 0;
	const int t_stat = isatty(0);

	while (1)
	{
		prompt(av[0]);
		buffer = exe_read(av[0], &rc);
		printf("%s\n", buffer);
		if (rc == 0)
			break;
		else if (rc == 1)
			continue;

		tmp = split_exe(buffer);
		(void) tmp;
		return (1);
		exe = strtok(buffer, "\n"); 
		printf("%s\n", buffer);
		while (exe != NULL)
		{
			printf("%s\n", exe);
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
			printf("%s\n", exe);
			exe = strtok(NULL, "\n");
		}
		if (t_stat == 0)
			break;
		free(buffer);
	}
	free(buffer);
	return (e_status);
}
