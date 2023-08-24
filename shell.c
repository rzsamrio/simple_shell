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

		check = getline(&line, &len, stdin);
		if (check == -1 || line[0] == '\n')
		{
			if (check == -1)
			{
				_puts("\n", 1);
				free(line);
				exit(98);
			}
			continue;
		}
		else
		{
			if (line[_strlen(line) - 1] == '\n')
				line[_strlen(line) - 1] = '\0';

			check = fcall(line, av[0]);
			if (check == -1)
			{
				free(line);
				exit(98);
			}
		}

		if  (isatty(0) != 1)
			break;
	}
	free(line);
	return (0);
}
