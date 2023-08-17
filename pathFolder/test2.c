#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

extern char **environ;

char *fpath(char **env)
{
    char *pathv;
    int len, i;

    for (i = 0; env[i]; i++)
    {
        if (strncmp(env[i], "PATH=", 5) == 0)
        {
            len = strlen(env[i]) - 5;

            pathv = malloc(sizeof(char) * (len + 1));
            if(!pathv)
            {
                perror("Memory allocation problem");
                return (NULL);
            }

            strcpy(pathv, env[i] + 5);
            return (pathv);
        }
    }

    return (NULL);
}

char **spath(char **env)
{
	int i, num;
	char *buffer, **dir;
    char *path = fpath(env);

	for (i = 0, num = 0; path[i]; i++)
	{
    	if (path[i] == ':')
			num++;
    }

	dir = malloc(sizeof(char *) * (num + 2));
    if (!dir)
    {
        return (NULL);
    }
	buffer = strtok(path, ":");
	for (i = 0; buffer != NULL; i++)
	{
		dir[i] = buffer;
		buffer = strtok(NULL, ":");
	}
	dir[num + 1] = NULL;

	return (dir);
}

void free_spath(char **dir) {
    if (dir) 
    {
        for (int i = 0; dir[i]; i++)
        {
            free(dir[i]);
        }
        free(dir);
    }
}


int main(void)
{
    int i;
    char **dirs = spath(environ);

    for (i = 0; dirs[i]; i++)
    {
        printf("%s\n", dirs[i]);
    }

    free_spath(dirs);
    return (0);
}
