#include "main.h"
#include <string.h>

/**
 * main - shell remake
 * @ac: argument count
 * @av: argument array
 *
 * Return: always 0
*/
int main(int ac __attribute__((unused)), char **av)
{
	char *line = NULL, prompt[] = "($) ";
	size_t len = 0;
	int check;

	while (1)
	{
		if (isatty(0) == 1)
			write(1, &prompt, _strlen(prompt));

		fflush(stdout);
		if (getline(&line, &len, stdin) == -1)
		{
			_puts("\n", 1);
			free(line);
			exit(98);
		}
		else
		{
			check = fcall(line, av[0]);
			if (check == -1)
				exit(98);
			else if (check == 2 || check == 1)
				continue;
		}

		if  (isatty(0) != 1)
			break;
	}

	free(line);
	return (0);
}
