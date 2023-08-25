#include "main.h"

/**
 * ispath - Checks if execution is a path
 * @cmd: execution
 *
 * Return: 0 if false, 1 if true
 */
int ispath(char *cmd)
{
	int i;

	for (i = 0; cmd[i] != '\0'; i++)
	{
		if (cmd[i] == '/')
			return (1); /* is a path */
	}
	return (0);
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
	int n;

	n = _strlen(s);
	write(fd, s, n);
	return (n);
}

/**
 * err_handle - outputs error message with program name
 * @prog: program name
 *
 * Return: void
*/
void err_handle(char *prog)
{
	_puts(prog, 2);
	_puts(": ", 2);
	perror("");
}

/**
 * free_array - frees an array of d-alloc strings
 * @arr: array
 */
void free_array(char **arr)
{
	int i;

	for (i = 0; arr[i] != NULL; i++)
		free(arr[i]);
	free(arr);
}

