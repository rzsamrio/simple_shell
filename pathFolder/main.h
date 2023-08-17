#ifndef HEADER_H
#define HEADER_H

/* Header Files */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

/* Global Variables & Macros */



/* Function Declarations */
int _strlen(char *s);
int _puts(char *s, int std);
void err_handle(char *name);
char *_strcpy(char *dest, const char *src);
int _strncmp(const char *s1, const char *s2, int n);

#endif /* #ifndef HEADER_H */
