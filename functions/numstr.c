#include "main.h"

/**
 * num_len - returns length of a number
 * @n: the number
 *
 * Return: length of a number
 */
int num_len(int n)
{
	unsigned int n1;
	int length = 1;

	if (n < 0)
	{
		length++;
		n1 = n * -1;
	}
	else
		n1 = n;
	
    while (n1 > 9)
	{
		length++;
		n1 = n1 / 10;
	}

	return (length);
}
/**
 * reverse_atoi - converts int to string.
 * @n: number (int)
 *
 * Return: convrted number as a string
 */
char *reverse_atoi(int n)
{
	unsigned int n1;
	int len = num_len(n);
	char *buffer;

	buffer = malloc(sizeof(char) * (len + 1));
	if (buffer == 0)
		return (NULL);

	*(buffer + len) = '\0';

	if (n < 0)
	{
		n1 = n * -1;
		buffer[0] = '-';
	}
	else
	{
		n1 = n;
	}

	len--;
	do {
		*(buffer + len) = (n1 % 10) + '0';
		n1 = n1 / 10;
		len--;
	}
	while (n1 > 0)
		;
	return (buffer);
}

/**
 * _atoi - converts a string to an integer
 * @s: the string
 *
 * Return: conversion result
 */
int _atoi(char *s)
{
	unsigned int count = 0, size = 0, a = 0, sign = 1, div = 1, i;

	while (*(s + count) != '\0')
	{
		if (size > 0 && (*(s + count) < '0' || *(s + count) > '9'))
			break;

		if (*(s + count) == '-')
			sign *= -1;

		if ((*(s + count) >= '0') && (*(s + count) <= '9'))
		{
			if (size > 0)
				div *= 10;
			size++;
		}
		count++;
	}

	for (i = count - size; i < count; i++)
	{
		a = a + ((*(s + i) - 48) * div);
		div /= 10;
	}
	return (a * sign);
}
