#include "main.h"


int main(int ac __attribute__((unused)), char **av, char **env)
{
	int var_stat, exestat;
	const char n = '\n';
	char  *path, *cmd, **arg, **tmp, *buffer = NULL;
	size_t buf_len = 0;
	const int t_stat = isatty(0);  /* terminal var_stat */
	const int p_len = _strlen(av[0]); /* program length */
	pid_t child;

	while (1)
	{
		prompt(t_stat, p_len, av[0]);
		var_stat = getline(&buffer, &buf_len, stdin); /* bug: new line*/
		/*if (buffer[0] = '\n')
			continue;*/
		if (var_stat == -1)
		{
			write(1, &n, 1);
			break;
		}
		arg = get_arg(buffer, arg);
		printf("%s\n", arg[0]);
		/* 
		Path handling stats here
		 * Work on memory 
		 */
		exestat = ispath(arg[0]);
		if (exestat == 0)
		{
			tmp = clone_arr(env);
			path = get_var(tmp, "PATH");
			tmp = split_path(path);
			cmd = get_cmd(tmp, arg[0]);
			if (cmd == NULL)
			{
				err_handle(&p_len, av[0]);
				free(arg);
				free(path);
				continue;
			}
		}
		else
			cmd = arg[0];

		child = fork();
		if (child == -1)
		{
			err_handle(&p_len, av[0]);
			free(arg);
			free(buffer);
			exit(98);
		}

		if (child == 0)
		{
			var_stat = execve(cmd, arg, env);
			if (var_stat == -1)
			{
				err_handle(&p_len, av[0]);
				free(arg);
				break;
			}
		}
		waitpid(child, NULL, 0);
		free(arg);
		if (exestat == 0)
		{
			free(cmd);
			free(path);
		}
		if (t_stat == 0)
		{
			printf("breaking\n");
			break;
		}
	}
	free(buffer);
	return (0);
}
