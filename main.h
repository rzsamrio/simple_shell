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

/* process functions --> proc.c */
void prompt(char *p_name);
int specify(char *cmd, char **env);
char **get_arg(char *src, char **arr);
int p_handl(char **cmd, char **env, char *prog, char **exe);
int execute(char *cmd, char **env, char *prog, char **exe, char *buffer);

/* path functions --> path.c */
char *fpath(char *env[]);
char **split_path(char *path);
char *get_cmd(char *path_array[], char *cmd);

/* string Functions --> string.c */
int _strlen(const char *s);
int _strcmp(char *a, char *b);
int _strncmp(const char *s1, const char *s2, int n);
char *_strcat(char *str1, char *str2);
char *_strcpy(char *dest, char *src);

/* status & display functions --> status.c */
void err_handle(char *prog);
int ispath(char *cmd);
void free_array(char **arr);
int _puts(char *s, unsigned int fd);

/* obsolete functions */
char **clone_arr(char **array);
char *get_var(char **env, char *var);

#endif
