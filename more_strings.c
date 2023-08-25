#include "main.h"

/**
 * trim - removes whites spaces from execution line
 * @s: address of the execution line
 * Return: 0, 1, -1
 *
 * Returns 0 if untouched (no preceeding whitespace)
 * 1 if successfully trimmed
 * -1 if no command is met (invalid execution)
 */
int trim(char **s)
{
	int i, c;

	if (*s == NULL)
		return (0);
	if ((*s)[0] == ' ')
	{
		for (i = 0, c = i + 1; (*s)[i] == ' '; i++, c++)
		{
			if ((*s)[c] != ' ' && (*s)[c] != '\n' && (*s)[c] != '\0')
			{
				*s = &(*s)[c];
				return (1);
			}
		}
		return (-1);
	}
	return (0);
}

/**
 * _strtokr - Tokenizes a string by the delimeter
 * @s: string to Tokenize
 * @delim: delimeters
 * @sptr: Address of pointer to save string context
 * Return: Null terminated token or NULL if no delim are found
 *
 * Function tokenizes a string while saving it's context
 * in an external pointer for future reference of futher use
 */
char *_strtokr(char *s, char *delim, char **sptr)
{
	int i, j, c;

	if (delim == NULL || *sptr == NULL)
		return (NULL);

	if (s == NULL)
		s = *sptr;

	for (i = 0; delim[i]; i++)
	{
		for (j = 0, c = j + 1; s[j]; j++, c++)
		{
			if (s[j] == delim[i])
			{
				s[j] = '\0';
				if (s[c] != '\0')
				{
					if (s[c] != delim[i])
						*sptr = &s[c];
					else
						continue;
				}
				else
					*sptr = NULL;
				return (s);
			}
		}
	}

	*sptr = NULL;
	return (s);
}
