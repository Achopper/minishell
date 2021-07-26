#include "buildins/minishell.h"

void	sys_err_exit(t_data *data, char *err_msg, int code)
{
	ft_putstr_fd(err_msg, STDERR_FILENO);
	data->status = code;
	exit(code);
}

int	error_exit(t_data *data, int code)
{
	data->status = code;
	exit(code);
}
