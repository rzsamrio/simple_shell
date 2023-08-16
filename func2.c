/**		TO-DO
 * Fix memory leaks in your code
 * Write function: split_path()
 	* truncates our path variable gotten from get_path()
	* uses strtok(buffer, ":") to split them
	* store each one as elements of an array
 * Write function: find_path()
 	* concatenates our first argument with each PATH
 	* finds the location of our command function in PATH
	* returns a buffer containing the location
 * We then pass this buffer to our execve command
 * Done: get_path()
 	* Finds the PATH variable in our environment array and executes
 */
#include "main.h"


char **clone_arr(char **array)
{
	int i;
	char **clone;

	for (i = 0; array[i] != NULL; i++);
	clone = malloc(sizeof(char *) * (i + 1));
	for (i = 0; array[i] != NULL; i++)
		clone[i] = array[i];
	return (clone);
}

char **split_path(char *path)
{
	int i, num;
	char *buffer, **parr;

	for (i = 0, num = 0; path[i]; i++)
		if (path[i] == ':')
			num++;
	parr = malloc(sizeof(char *) * (num + 2));
	buffer = strtok(path, ":");
	for (i = 0; buffer != NULL; i++)
	{
		parr[i] = buffer;
		buffer = strtok(NULL, ":");
	}
	parr[num + 1] = NULL;
	return (parr);
}

char *get_cmd(char **path_array, char *cmd)
{
	int i, status;
	char *tmp;
	struct stat file;

	for (i = 0; path_array[i] != NULL; i++)
	{
		tmp = _strcat(path_array[i], cmd);
		status = stat(tmp, &file);
		if (status == 0)
		{
			return(tmp);
		}
		free(tmp);
	}
	return (NULL);
}

char *_strcat(char *str1, char *str2)
{
	char *merge;
	int i, j, len;
	
	len = _strlen(str1) + _strlen(str2);
	merge = malloc(len + 2);
	
	for (i = 0; str1[i] != '\0'; i++)
		merge[i] = str1[i];
	merge[i] = '/';
	i++;
	for (j = 0; str2[j] != '\0'; j++, i++)
		merge[i] = str2[j];
	merge[i] = '\0';
	return (merge);
}
