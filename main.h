#ifndef __SHELL__H
#define __SHELL__H

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

#define PT_LEN 4 /* Prompt size */
#define ULIMIT 1024
#define FREE_ARGS char **arg, char *buffer /* args passed to be freed */
#define EXEC char **exe, char **ptr /* Allows for proper execution lines */
#define INTS int *line, int *x /* Line number and exit status */

extern char **environ;

/* process functions --> proc.c proc2.c*/
void prompt(char *p_name);
int specify(char *cmd, char **env, INTS, FREE_ARGS, EXEC);
char **get_arg(char *src, char **arr);
int p_handl(char **cmd, char **env, char *prog, char **arg, INTS, EXEC);
int execute(char *cmd, char **env, char *prog, FREE_ARGS);
char *exe_read(char *prog, int *len, int *line);
char **split_exe(char *s);
int trimexe(char **exe, char **ptr, int *line);

/* path functions --> path.c */
char *fpath(char *env[]);
char **split_path(char *path);
char *get_cmd(char *path_array[], char *cmd);

/* string Functions --> string.c, more_strings.c */
int _strlen(const char *s);
int _strcmp(char *a, char *b);
int _strncmp(const char *s1, const char *s2, int n);
char *_strcat(char *str1, char *str2);
char *_strcpy(char *dest, char *src);
char *_strtokr(char *s, char *delim, char **sptr);
int trim(char **s);

/* status & display functions --> status.c */
void err_handle(char *prog);
int ispath(char *cmd);
void free_array(char **arr);
int _puts(char *s, unsigned int fd);
char *nocmd(char *prog, int line, char *cmd, const char *error);

/* obsolete functions */
char **clone_arr(char **array);
char *get_var(char **env, char *var);


#endif
