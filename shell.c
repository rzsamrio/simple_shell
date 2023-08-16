#include "main.h"


int main(int ac, char **av, char **env)
{
	int prog_len, status;
	char *path, *cmd, n = '\n';
	char **arg, **tmp, *buffer = NULL;
	size_t buf_len = 0;
	pid_t child;

	prog_len = _strlen(av[0]);
	(void) ac;
	while (1)
	{ 
		if (isatty(0) == 1)
		{
			status = write(1, "sam$ ", PT_LEN);
			if (status == -1)
			{
				err_handle(&prog_len, av[0]);
				exit(98);
			}
		}
		status = getline(&buffer, &buf_len, stdin);
		if (status == -1)
		{
			write(1, &n, 1);
			break;
		}
		arg = get_arg(buffer, arg);
		/* Path handling stats here, commented out the lines
		 * some bugs need handling 
		tmp = clone_arr(env);
		path = get_var(tmp, "PATH");
		free(tmp);
		tmp = split_path(path);
		cmd = get_cmd(tmp, arg[0]);
		if (cmd == NULL)
		{
			err_handle(&prog_len, av[0]);
			continue;
		}
		*/
		child = fork();
		if (child == -1)
		{
			err_handle(&prog_len, av[0]);
			free(arg);
			free(buffer);
			exit(98);
		}

		if (child == 0)
		{
			status = execve(arg[0], arg, env);
			if (status == -1)
			{
				err_handle(&prog_len, av[0]);
				free(arg);
				break;
			}
		}
		waitpid(child, NULL, 0);
		free(arg);
		if (isatty(0) != 1)
			break;
	}
	free(buffer);
	return (0);
}
