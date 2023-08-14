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
	perror(": Error ");
}

char **get_arg(char *src, char **arr, int *count)
{
	int i;
	char *buffer;

	for (i = 0, *count = 0; src[i] != '\0'; i++)
		if (src[i] == ' ' || src[i] == '\n')
			(*count)++;
	arr = malloc(sizeof(char *) * (*count + 1));
	buffer = strtok(src, " \n");
	for (i = 0; buffer != NULL; i++)
	{
		arr[i] = buffer;
		buffer = strtok(NULL, " \n");
	}
	arr[*count] = NULL;
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

char *find_path(char **env)
{
	int i;
	char *buffer;

	for (i = 0; env[i] != NULL; i++)
	{
		buffer = strtok(env[i], "=");
		if (_strcmp(buffer, "PATH") == 0)
		{
			buffer = strtok(NULL, "=");
			printf("%s\n", buffer);
			return (buffer);
		}
	}
}


