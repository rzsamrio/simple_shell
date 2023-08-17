#include "main.h"

int _strlen(char *s)
{
    int i = 0; 

    while (s[i] != '\0')
        i++;

    return (i);
}


int _puts(char *s, int std)
{
    int i = 0;

    while (s[i])
        write(std, &s[i++], 1);

    return (i + 1);
}

int _strncmp(const char *s1, const char *s2, int n)
{
    int count = 0;

    while (n > 0 && (*s1 == *s2))
    {
        if (*s1 == '\0')
            return (0);

        s1++;
        s2++;
        n--;
    }

    return ((n == 0) ? 0 : (*s1 - *s2));
}

char *_strcpy(char *dest, const char *src)
{
    int i;

    if (!dest)
        return NULL;

    for (i = 0; src[i]; i++)
        dest[i] = src[i];

    dest[i] = '\0';

    return (dest);
}

void err_handle(char *name)
{
    _puts(name, 2);
    _puts(": No such file or directory\n", 2);
}
