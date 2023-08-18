#include "main.h"

int _strlen(const char *s)
{
	int i;

	for (i = 0; s[i] != 0; i++);
	return (i);
}

void err_handle(int *n, char *str)
{
	write(1, str, *n);
	write(1, ": ", 2);
	perror("");
}

char **get_arg(char *src, char **arr)
{
	int i, count;
	char *buffer;

	for (i = 0, count = 0; src[i] != '\0'; i++)
		if (src[i] == ' ' || src[i] == '\n')
			count++;
	arr = malloc(sizeof(char *) * (count + 1));
	buffer = strtok(src, " \n");
	for (i = 0; buffer != NULL; i++)
	{
		arr[i] = buffer;
		buffer = strtok(NULL, " \n");
	}
	arr[count] = NULL;
	return (arr);
}

int _strcmp(char *a, char *b)
{
	int i;

	for (i = 0; a[i] == b[i]; i++)
		if (a[i] == 0)
			return (0);
	return (a[i] - b[i]);
}

char *get_var(char **env, char *var)
{
	int i, size, j;
	char *buffer, *tmp;

	for (i = 0; env[i] != NULL; i++)
	{
		buffer = strtok(env[i], "=");
		if (_strcmp(buffer, var) == 0)
		{
			buffer = strtok(NULL, "=");
			size = _strlen(buffer);
			tmp = malloc(size + 1);
			tmp = _strcpy(tmp, buffer);
			free_array(env);
			return (tmp);
		}
	}
	return (NULL);
}

