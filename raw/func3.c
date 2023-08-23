#include "main.h"

int ispath(char *cmd)
{
	int i;

	for(i = 0; cmd[i] != '\0'; i++)
	{
		if (cmd[i] == '/')
			return (1); /* is a path */
	}
	return (0);
}

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

void free_array(char **arr)
{
	int i;

	for (i = 0; arr[i] != NULL; i++)
		free(arr[i]);
	free(arr);
}

