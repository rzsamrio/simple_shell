#include "main.h"

/**
 * _strlen - computes the length of a string
 * @s: pointer to the string
 *
 * Return: number of characters in the string 's'
*/
int _strlen(char *s)
{
	int i = 0;

	while (s[i] != '\0')
		i++;

	return (i);
}

char *_strcat(char *s1, char *s2)
{
	char *str;
	int i, j;

	str = malloc(_strlen(s1) + _strlen(s2) + 2);

	for (i = 0; s1[i]; i++)
		str[i] = s1[i];

	str[i] = '/';
	i++;

	for (j = 0; s2[j]; i++, j++)
		str[i] = s2[j];

	str[i] = '\0';

	return (str);
}

/**
 * _strncmp - compares the first n bytes/characters of s1 and s2
 * @s1: pointer to the 1st string
 * @s2: pointer to the 2nd string
 * @n: number of bytes to compare
 *
 * Return: ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓
 * ------>     0     if s1 and s2 are equal
 * ------> (+) value if s1 is   less  than s2
 * ------> (-) value if s1 is greater than s2
*/
int _strncmp(const char *s1, const char *s2, int n)
{
	while (n > 0 && (*s1 == *s2))
	{
		if (*s1 == '\0')
			return (0);

		s1++;
		s2++;
		n--;
	}

	return ((n == 0) ? 0 : (*s1 - *s2));
}

/**
 * _strcpy - copies a string
 * @dest: the destination string
 * @src: the source string
 *
 * Return: pointer to the result/dest
*/
char *_strcpy(char *dest, const char *src)
{
	int i;

	if (!dest)
		return (NULL);

	for (i = 0; src[i]; i++)
		dest[i] = src[i];

	dest[i] = '\0';

	return (dest);
}

int _strcmp(char *a, char *b)
{
        int i;

        for (i = 0; a[i] == b[i]; i++)
                if (a[i] == 0)
                        return (0);
        return (a[i] - b[i]);
}

