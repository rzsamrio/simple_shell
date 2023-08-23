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

/**
 * _puts - output strings to STDOUT/STDERR
 * @s: the string to print
 * @fd: file descriptor value
 * --> 1 is for STDOUT
 * --> 2 is for STDERR
 *
 * Return: length of the string
*/
int _puts(char *s, unsigned int fd)
{
	int i = 0;

	if (fd != 1 && fd != 2)
		fd = 1;


	while (s[i])
		write(fd, &s[i++], 1);

	return (i + 1);
}

/**
 * err_handle - outputs error message with program name
 * and frees memory
 * @prog: program name
 * @a: string array to be freed
 * @b: string array to be freed
 * @c: string to be freed
 *
 * Return: void
*/
void err_handle(char *prog, char **a, char **b, char *c)
{
	if (a)
		free(a);
	if (b)
		free(b);
	if (c)
		free(c);

	if (prog)
	{
		_puts(prog, 2);
		_puts(": ", 2);
		perror("");
	}
}
