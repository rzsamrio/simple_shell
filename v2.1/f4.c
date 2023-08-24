#include "main.h"
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

	while (s[i])
		write(fd, &s[i++], 1);

	return (i + 1);
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
