#include "main.h"
#include <stdio.h>

/**
 * exe_read - reads from the command line
 * @prog: program name
 * @len: length read
 *
 * Return: string containing user input
 * or NULL on new line
 */

char *exe_read(char *prog, int *len)
{
	char *buffer;
	const char n = '\n';

	buffer = malloc(sizeof(char) * 1024);
	if (buffer == NULL)
	{
		err_handle(prog);
		exit(98);
	}

	*len = read(0, buffer, 1024);
	if (*len == -1)
	{
		err_handle(prog);
		exit(98);
	}
	else if (*len == 0)
	{
		write(1, &n, 1);
		return (buffer);
	}

	if (buffer[0] == '\n')
	{
		free(buffer);
		*len = 1;
		return (NULL);
	}
	buffer[*len] = '\0';
	return (buffer);
}

/**
 * split_exe - splits multiple commands into an array
 * @s: string containing commands
 * Return: array
 */
char **split_exe(char *s)
{
	int i, count;
	char **arr, *tmp;

	for (i = 0, count = 0; s[i]; i++)
		if (s[i] == '\n')
			count++;
	arr = malloc(sizeof(char *) * (count + 1));
	tmp = strtok(s, "\n");
	printf("%s\n", s);
	for (i = 0; tmp != NULL; i++)
	{
		arr[i] = tmp;
		tmp = strtok(NULL, "\n");
	}
	arr[count] = NULL;
	return (arr);
}

char *_strtokr(char *s, char *delim, char **sptr)
{
	int i, j;

	if (delim == NULL || *sptr == NULL)
		return (NULL);
	
	if (s == NULL)
		s = *sptr;

	for (i = 0; delim[i]; i++)
	{
		for (j = 0; s[j]; j++)
		{
			if (s[j] == delim[i])
			{
				if (s[j + 1] != '\0')
					*sptr = &s[j + 1];
				else
					*sptr = NULL;
				s[j] = '\0';
				return (s);
			}
		}
	}

	*sptr = NULL;
	return (s);
}
