#include "main.h"

/**
 * mem_line - memory management for line input
 * @linep: input buffer
 * @buffer: string called to linep
 * @ls: line size
 * @bs: buffer size
 *
 * Return: void
 */
void mem_line(char **linep, size_t *ls, char *buffer, size_t bs)
{

	if (*linep == NULL)
	{
		if  (bs > LINE_SIZE)
			*ls = bs;

		else
			*ls = LINE_SIZE;
		*linep = buffer;
	}
	else if (*ls < bs)
	{
		if (bs > LINE_SIZE)
			*ls = bs;
		else
			*ls = LINE_SIZE;

		*linep = buffer;
	}
	else
	{
		_strcpy(*linep, buffer);
		free(buffer);
	}
}

/**
 * get_line - getline remake
 * @linep: input buffer
 * @n: size of linep
 * @stream: reading location
 *
 * Return: The number of bytes
 */
ssize_t get_line(char **linep, size_t *n, FILE *stream)
{
	static ssize_t nc;
	ssize_t count;
	char *buffer;
	char r = 'a';
	int i;

	if (nc == 0)
		fflush(stream);
	else
		return (-1);
	nc = 0;

	buffer = malloc(sizeof(char) * LINE_SIZE);
	if (!buffer)
		return (-1);
	while (r != '\n')
	{
		i = read(STDIN_FILENO, &r, 1);
		if (i == -1 || (i == 0 && nc == 0))
			return (s_free(buffer));

		if (i == 0 && nc != 0)
		{
			nc++;
			break;
		}
		if (nc >= LINE_SIZE)
			buffer = _realloc(buffer, nc, nc + 1);
		buffer[nc] = r;
		nc++;
	}
	buffer[nc] = '\0';
	mem_line(linep, n, buffer, nc);
	count = nc;
	if (i != 0)
		nc = 0;
	return (count);
}

/**
 * s_free - frees a string and returns -1
 * @buffer: the string to be freed
 *
 * Return: always -1
*/
int s_free(char *buffer)
{
	if (buffer)
		free(buffer);

	return (-1);
}
