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


void free_array(char **arr)
{
	int i;

	for (i = 0; arr[i] != NULL; i++)
		free(arr[i]);
	free(arr);
}

