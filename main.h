#ifndef __SHELL__H
#define __SHELL__H

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

#define PT_LEN 4 /* Prompt size */

extern char **environ;

void prompt(char *p_name);
int specify(char *cmd, char **env);
int _strlen(const char *s);
int _strcmp(char *a, char *b);
int _strncmp(const char *s1, const char *s2, int n);
char **get_arg(char *src, char **arr);
char *get_var(char **env, char *var);
char **split_path(char *path);
char *_strcat(char *str1, char *str2);
char *get_cmd(char *path_array[], char *cmd);
void err_handle(char *prog);
char **clone_arr(char **array);
int ispath(char *cmd);
char *_strcpy(char *dest, char *src);
void free_array(char **arr);
int _puts(char *s, unsigned int fd);
char *fpath(char *env[]);
int p_handl(char **cmd, char **env, char *prog, char **exe, char *buffer);
int execute(char *cmd, char **env, char *prog, char **exe, char *buffer);
#endif
