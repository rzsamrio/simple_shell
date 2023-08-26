#include "main.h"

/**
 * exec_line - finds builtins and commands
 * @vars: sh_var struct
 *
 * Return: 1 if ran successfuly
 */
int exec_line(sh_var *vars)
{
	int (*builtin)(sh_var *vars);

	if (vars->args[0] == NULL)
		return (1);

	builtin = fbuiltin(vars->args[0]);

	if (builtin != NULL)
		return (builtin(vars));

	return (cmd_exec(vars));
}

/* Loop Functions */

/**
 * del_comment - deletes input comments
 * @in: input
 *
 * Return: no comment input
 */
char *del_comment(char *in)
{
	int i, up_to;

	up_to = 0;
	for (i = 0; in[i]; i++)
	{
		if (in[i] == '#')
		{
			if (i == 0)
			{
				free(in);
				return (NULL);
			}

			if (in[i - 1] == ' ' || in[i - 1] == '\t' || in[i - 1] == ';')
				up_to = i;
		}
	}

	if (up_to != 0)
	{
		in = _realloc(in, i, up_to + 1);
		in[up_to] = '\0';
	}

	return (in);
}

/**
 * shell_loop - Loop of shell
 * @vars: data relevant (av, input, args)
 *
 * Return: no return.
 */
void shell_loop(sh_var *vars)
{
	int loop, i_eof;
	char *input;

	loop = 1;
	while (loop == 1)
	{
		write(STDIN_FILENO, "($) ", 4);
		input = read_line(&i_eof);
		if (i_eof != -1)
		{
			input = del_comment(input);
			if (input == NULL)
				continue;

			if (check_syntax_error(vars, input) == 1)
			{
				vars->status = 2;
				free(input);
				continue;
			}
			input = rep_var(input, vars);
			loop = split_commands(vars, input);
			vars->counter += 1;
			free(input);
		}
		else
		{
			loop = 0;
			free(input);
		}
	}
	free(input);
}

