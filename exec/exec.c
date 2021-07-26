#include "../buildins/minishell.h"

void	make_redir(t_data *data)
{
	if (data->redir_fd0 != -2)
	{
		dup2(data->redir_fd0, 0);
		close(data->redir_fd0);
	}
	if (data->redir_fd1 != -2)
	{
		dup2(data->redir_fd1, 1);
		close(data->redir_fd1);
	}
}

void	do_cmd(t_data *data, char **args, t_command *tmp_cmd)
{
	char		*cmd;

	cmd = get_binary(data, args, -1);
	ignore_signals();
	data->pid = fork();
	if (data->pid == 0)
	{
		if (data->err)
			errno = data->err;
		set_signal_to_def();
		check_fd(tmp_cmd, args);
		close_child_fds(data);
		make_redir(data);
		if (!cmd || cmd[0] == '\0')
			exit(perr(args[0], 0, "command not found", 127));
		if (is_dir(args[0]))
			exit(perr(args[0], 0, strerror(errno), 127));
		execve(cmd, args, data->env_arr);
		data->status = 1;
		if (errno == 13)
			exit(perr(args[0], 0, strerror(errno), 126));
		exit(perr(args[0], 0, strerror(errno), 127));
	}
	init_parent_signals();
	free(cmd);
}

void	get_status(t_data *data, int i)
{
	pid_t	pid;
	int		status;

	if (data->pid == -1 || ft_memcmp(data->input, "\0", 1) == 0)
	{
		data->status = 0;
		return ;
	}
	while (i--)
	{
		pid = wait(&status);
		if (pid <= 0)
			break ;
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		else
		{
			write(1, "\r", 1);
			status = WTERMSIG(status) + 128;
			if (pid == data->pid && status == 131)
				write(2, "Quit: 3\n", ft_strlen("Quit: 3\n"));
		}
		if (pid == data->pid)
			data->status = status;
	}
}

void	execute(t_command *tmp_cmd, t_data *data, char **args, int *i)
{
	while (tmp_cmd)
	{
		args = tmp_cmd->args;
		if (!args[0])
		{
			check_bild_fd(data, tmp_cmd);
			if (tmp_cmd->next)
			{
				tmp_cmd = tmp_cmd->next;
				continue ;
			}
			else
				break ;
		}
		create_pipe_redir_fd1(data, *i);
		data->redir_fd1 = tmp_cmd->fd_out;
		data->redir_fd0 = tmp_cmd->fd_in;
		if (is_built(args[0]))
			do_built(data, args, tmp_cmd);
		else
			do_cmd(data, args, tmp_cmd);
		redir_fd0_close_pipe(data);
		tmp_cmd = tmp_cmd->next;
		*i += 1;
	}
}

void	exec(t_data *data, int i)
{
	t_command	*tmp_cmd;
	char		**args;

	tmp_cmd = data->comm_lst;
	args = NULL;
	save_fds(data);
	execute(tmp_cmd, data, args, &i);
	restore_fds(data);
	get_status(data, i);
}
