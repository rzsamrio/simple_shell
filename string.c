#include "main.h"

/**
 * strlen - finds the length of a string
 * @s: string
 *
 * Return: length
 */
int _strlen(const char *s)
{
	int i;

	i = 0;
	while (s[i] != 0)
		i++;
	return (i);
}

/**
 * _strcmp - compares 2 strings
 * @a: string 1
 * @b: string 2
 *
 * Return: 0 if similar, difference if not
 */
int _strcmp(char *a, char *b)
{
	int i;

	for (i = 0; a[i] == b[i]; i++)
		if (a[i] == 0)
			return (0);
	return (a[i] - b[i]);
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
	int i;

	i = 0;
	while (n > 0 && (s1[i] == s2[i]))
	{
		if (s1[i] == '\0')
			return (0);
		i++;
		n--;
	}

	return ((n == 0) ? 0 : (s1[i] - s2[i]));
}

/**
 * _strcpy - copies 2 strings
 * @dest: destination strings'
 * @src: source string
 *
 * Return: address of dest
 */
char *_strcpy(char *dest, char *src)
{
	int i;

	if (!dest)
		return (NULL);
	for (i = 0; src[i]; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

/**
 * _strcat - dynamically concatenates with path /
 * @str1: path string
 * @str2: executable name
 *
 * Return: PATH of execution
 */
char *_strcat(char *str1, char *str2)
{
	char *merge;
	int i, j, len;

	len = strlen(str1) + strlen(str2);
	merge = malloc(len + 2);

	for (i = 0; str1[i] != '\0'; i++)
		merge[i] = str1[i];
	merge[i] = '/';
	i++;
	for (j = 0; str2[j] != '\0'; j++, i++)
		merge[i] = str2[j];
	merge[i] = '\0';
	return (merge);
}
