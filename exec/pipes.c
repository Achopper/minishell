#include "../buildins/minishell.h"

void	create_pipe_redir_fd1(t_data *data, int i)
{
	int	pipe_er;

	pipe_er = pipe(data->pipe);
	if (pipe_er == -1)
	{
		ft_putstr_fd("pipe error\n", STDERR_FILENO);
		exit(1);
	}
	if (data->pipe_num + 1 - i > 1)
	{
		dup2(data->pipe[1], 1);
	}
	else
	{
		dup2(data->fd1, 1);
	}
}

void	save_fds(t_data *data)
{
	data->fd0 = dup(0);
	data->fd1 = dup(1);
}

void	close_child_fds(t_data *data)
{
	close(data->pipe[0]);
	close(data->pipe[1]);
	close(data->fd0);
	close(data->fd1);
}

void	redir_fd0_close_pipe(t_data *data)
{
	dup2(data->pipe[0], 0);
	close(data->pipe[0]);
	close(data->pipe[1]);
}

void	restore_fds(t_data *data)
{
	dup2(data->fd0, 0);
	dup2(data->fd1, 1);
	close(data->fd0);
	close(data->fd1);
}
