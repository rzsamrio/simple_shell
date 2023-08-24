#include "main.h"

/**
 * main - simple shell
 * @av: cla
 * @ac: number of cla
 * Return: 0
 */
int main(int ac __attribute__((unused)), char **av)
{
	char *cmd, **arg, *buffer = NULL;
	const char n = '\n';
	size_t buf_len = 0;

	while (1)
	{
		prompt(av[0]);
		if (getline(&buffer, &buf_len, stdin) == -1)
		{
			write(1, &n, 1);
			break;
		}
		if (buffer[0] == '\n')
			continue;
		arg = get_arg(buffer, arg);
		if (specify(arg[0], environ) == 1)
			continue;

		if (ispath(arg[0]) == 0)
		{
			if (p_handl(&cmd, environ, av[0], arg, buffer) == 1)
			{
				if (isatty(0) == 0)
					break;
				continue;
			}
		}
		else
			cmd = arg[0];
		
		if (execute(cmd, environ, av[0], arg, buffer) == 1)
			continue;
		if (ispath(arg[0]) == 0)
			free(cmd);
		/*	free(path); */
		free(arg);
	}
	free(buffer);
	return (0);
}
