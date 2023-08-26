#include "main.h"

/**
 * main - simple shell
 * @av: cla
 * @ac: number of cla
 * Return: 0
 */
int main(int ac __attribute__((unused)), char **av)
{
	char *cmd, **arg, *buffer, *exe, *ptr;
	char *ty[] = {"PATH=", NULL};
	int st, n = 1, e_status = 0;

	while (1)
	{
		prompt(av[0]);
		buffer = exe_read(av[0], &st);
		if (st == 0)
			break;
		else if (st == 1)
			continue;

		ptr = buffer; /* dummy init */
		exe = _strtokr(buffer, "\n", &ptr);
		while (exe != NULL)
		{
			if (trimexe(&exe, &ptr) == -1)
				continue;
			arg = get_arg(exe, arg);

			if (specify(arg[0], environ, e_status, arg, buffer, &exe, &ptr) == 1)
				continue;

			if (ispath(arg[0]) == 0)
			{
				st = p_handl(&cmd, ty, av[0], arg, n, &e_status, &exe, &ptr);
				if (st == 1 || st == -1)
					continue;
			}
			else
				cmd = arg[0];
			e_status = execute(cmd, ty, av[0], arg, buffer);
			exe = _strtokr(NULL, "\n", &ptr);
			n++;
		}

		if (isatty(0) == 0)
			break;
		free(buffer);
	}
	free(buffer);
	return (e_status);
}
