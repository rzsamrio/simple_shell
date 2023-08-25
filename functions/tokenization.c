#include "main.h"

/**
 * split_line - tokenizes the given string
 * @line: the string.
 *
 * Return: array of strings (line splitted)
 */
char **split_line(char *line)
{
	size_t bsize, i;
	char **tokens, *token;
	char *delim = " \t\r\a\n";

	bsize = TOKEN_SIZE;
	tokens = malloc(sizeof(char *) * (bsize));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = _strtok(line, delim);
	tokens[0] = token;

	for (i = 1; token != NULL; i++)
	{
		if (i == bsize)
		{
			bsize += TOKEN_SIZE;
			tokens = _reallocdp(tokens, i, sizeof(char *) * bsize);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = _strtok(NULL, delim);
		tokens[i] = token;
	}

	return (tokens);
}
