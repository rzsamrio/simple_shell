#include "main.h"


int main(int ac, char **av, char **env)
{
	int i, prog_len, status, argc = 0;
	char n = '\n';
	char **arg, *buffer = NULL;
	size_t buf_len = 0;
	pid_t child;
	const char *prompt;

	prog_len = _strlen(av[0]);
	(void) ac;
	while (1)
	{
		if (isatty(0) == 1)
		{
			prompt = "sam$ ";
			write(1, prompt, PT_LEN);
			if (status == -1)
			{
				err_handle(&prog_len, av[0]);
				break;
			}
		}
		status = getline(&buffer, &buf_len, stdin);
		if (status == -1)
		{
			write(1, &n, 1);
			break;
		}
		arg = get_arg(buffer, arg, &argc);
		child = fork();
		if (child == -1)
		{
			err_handle(&prog_len, av[0]);
			break;
		}

		if (child == 0)
		{
			status = execve(arg[0], arg, env);
			if (status == -1)
			{
				err_handle(&prog_len, av[0]);
				break;
			}
		}

		waitpid(child, NULL, 0);
		free(arg);
		if (isatty(0) != 1)
			break;
	}
	/* leaks still possible, optimise memory */
	free(buffer);
	return (0);
}
