#ifndef __SHELL__H
#define __SHELL__H

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

#define PT_LEN 5 /* Prompt size */

extern char **environ;

int _strlen(const char *s);
int _strcmp(char *a, char *b);
void err_handle(int *n, char *str);
char **get_arg(char *src, char **arr);
char *get_var(char **env, char *var);
char **split_path(char *path);
char *_strcat(char *str1, char *str2);
char *get_cmd(char **path_array, char *cmd);
char **clone_arr(char **array);


#endif
