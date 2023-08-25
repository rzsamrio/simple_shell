#include "main.h"

/**
 * _strlen - computes the length of a string
 * @s: pointer to the string
 *
 * Return: number of characters in the string 's'
*/
int _strlen(const char *s)
{
	int i = 0;

	while (s[i] != '\0')
		i++;

	return (i);
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
 * _strcmp - compares two strings.
 * @s1: 1st string
 * @s2: 2nd string
 *
 * Return: 0 -> s1 & s2 are equal
 * ------- 1 -> s1 greater than s2
 * ------ -1 -> s1 less than s2
 */
int _strcmp(char *s1, char *s2)
{
	int i;

	for (i = 0; s1[i] == s2[i] && s1[i]; i++)

	if (s1[i] > s2[i])
		return (1);

	if (s1[i] < s2[i])
		return (-1);

	return (0);
}

/**
 * _strchr - locates character in a string,
 * @s: the string
 * @c: the character
 *
 * Return: pointer to the matched character
 * or '\0' if the character is not found
 */
char *_strchr(char *s, char c)
{
	int i = 0;

	for (; *(s + i) != '\0'; i++)
		if (*(s + i) == c)
			return (s + i);

	if (*(s + i) == c)
		return (s + i);

	return ('\0');
}

/**
 * _strspn - gets the length of a prefix substring
 * @s: initial segment
 * @accept: accepted bytes
 *
 * Return: number of accepted bytes in the initial segment
 */
int _strspn(char *s, char *accept)
{
	int i, j, bool;

	for (i = 0; *(s + i) != '\0'; i++)
	{
		bool = 1;
		for (j = 0; *(accept + j) != '\0'; j++)
		{
			if (*(s + i) == *(accept + j))
			{
				bool = 0;
				break;
			}
		}
		if (bool == 1)
			break;
	}

	return (i);
}
