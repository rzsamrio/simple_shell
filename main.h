#ifndef __SHELL__H
#define __SHELL__H

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>


#define PT_LEN 5 /* Prompt size */

int _strlen(const char *s);
int _strcmp(char *a, char *b);
void err_handle(int *n, char *str);
char **get_arg(char *src, char **arr, int *count);
#endif
