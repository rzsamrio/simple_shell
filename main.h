#ifndef HEADER_H
#define HEADER_H

/* Header Files */
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

/* Global Variables & Macros */
extern char **environ;

/* Function Declarations */

    /* String/Error Handling           --> file: f1.c */
int _strlen(char *s);
char *_strcpy(char *dest, const char *src);
int _strncmp(const char *s1, const char *s2, int n);
int _puts(char *s, unsigned int fd);
void err_handle(char *prog, char **a, char **b, char *c);

    /* Process Handling / tokenization --> file: f2.c */
int fcall(char *line, char *prog);
char **tokenize(char *line);

    /* PATH handling                   --> file: f3.c */
int ispath(char *cmd);
char *fpath(char **env);
char **spath(char **env);
char *fetchc(char **path, char *cmd);
char *_strcat(char *s1, char *s2);

#endif /* #ifndef HEADER_H */
