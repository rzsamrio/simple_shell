#include "main.h"

/**
 * numcheck - checks if a string is a number
 * @s: the string
 *
 * Return: 1 if string is a number
 * 0 if not
 */
int numcheck(const char *s)
{
	int i;

	for (i = 0; s[i]; i++)
	{
		if (s[i] < 48 || s[i] > 57)
			return (0);
	}
	return (1);
}

/**
 * _strdup - duplicates a string
 * @s: the string
 *
 * Return: pointer to duplicated sstring
 * NULL, if insufficient memory was available
 */
char *_strdup(const char *s)
{
	char *dup;
	int len;

	len = _strlen(s);

	dup = malloc(sizeof(char) * (len + 1));
	if (dup == NULL)
		return (NULL);

	_memcpy(dup, s, len + 1);
	return (dup);
}

/**
 * charcmp - compares chararters of a string
 * @s: the string
 * @delim: delimiter
 *
 * Return: 1 if they are the same
 * 0 if not
*/
int charcmp(char s[], const char *delim)
{
	int i, j, k;

	for (i = 0, k = 0; s[i]; i++)
	{
		for (j = 0; delim[j]; j++)
		{
			if (s[i] == delim[j])
			{
				k++;
				break;
			}
		}
	}

	if (i == k)
		return (1);

	return (0);
}

/**
 * _strtok - splits a string using delimiters
 * @str: the string
 * @delim: delimiter(s)
 *
 * Return: the splitted string
 */
char *_strtok(char str[], const char *delim)
{
	static char *split, *end;
	char *start;
	unsigned int i, bool;

	if (!str)
	{
		if (charcmp(str, delim))
			return (NULL);
		split = str;
		i = _strlen(str);
		end = &str[i];
	}
	start = split;
	if (start == end)
		return (NULL);

	for (bool = 0; *split; split++)
	{
		if (split != start)
			if (*split && *(split - 1) == '\0')
				break;

		for (i = 0; delim[i]; i++)
		{
			if (*split == delim[i])
			{
				*split = '\0';
				if (split == start)
					start++;
				break;
			}
		}
		if (bool == 0 && *split)
			bool = 1;
	}
	if (bool == 0)
		return (NULL);

	return (start);
}

/**
 * _strcat - concatenates two strings
 * @s1: 1st string
 * @s2: 2nd string
 *
 * Return: the concatenated string
 */
char *_strcat(char *s1, const char *s2)
{
	int i;
	int j;

	for (i = 0; s1[i] != '\0'; i++)

	for (j = 0; s2[j] != '\0'; j++)
	{
		s1[i] = s2[j];
		i++;
	}

	s1[i] = '\0';

	return (s1);
}
