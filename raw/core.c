#include "main.h"

void prompt(int t_stat, int f_len, char *p_name)
{
	int status;

	if (t_stat == 1)
	{
		status = write(1, "($) ", PT_LEN);
		if (status == -1)
		{
			err_handle(&f_len, p_name);
			exit(98);
		}
	}
}

