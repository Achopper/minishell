#include "minishell.h"

int	is_built(char *arg)
{
	size_t	arg_len;

	arg_len = ft_strlen(arg);
	if ((ft_strncmp(arg, "export", ft_strlen("export")) == 0 && arg_len == 6) || \
		(ft_strncmp(arg, "unset", ft_strlen("unset")) == 0 && arg_len == 5) || \
		(ft_strncmp(arg, "echo", ft_strlen("echo")) == 0 && arg_len == 4) || \
		(ft_strncmp(arg, "exit", ft_strlen("exit")) == 0 && arg_len == 4) || \
		(ft_strncmp(arg, "pwd", ft_strlen("pwd")) == 0 && arg_len == 3) || \
		(ft_strncmp(arg, "env", ft_strlen("env")) == 0 && arg_len == 3) || \
		(ft_strncmp(arg, "cd", ft_strlen("cd")) == 0 && arg_len == 2))
		return (1);
	return (0);
}

void	fork_built(t_data *data, char **args, t_command *tmp_cmd)
{
	ignore_signals();
	data->pid = fork();
	if (data->pid == -1)
		sys_err_exit(data, FRK_ERR, 1);
	if (data->pid == 0)
	{
		check_fd(tmp_cmd, args);
		set_signal_to_def();
		if (ft_strncmp(args[0], "echo", ft_strlen("echo")) == 0)
			my_echo(args);
		else if (ft_strncmp(args[0], "cd", ft_strlen("cd")) == 0)
			my_cd(data, args);
		else if (ft_strncmp(args[0], "pwd", ft_strlen("pwd")) == 0)
			my_pwd();
		else if (ft_strncmp(args[0], "env", ft_strlen("env")) == 0)
			my_env(data);
		else if (ft_strncmp(args[0], "unset", ft_strlen("unset")) == 0)
			my_unset(data, args, 1);
		else if (ft_strncmp(args[0], "export", ft_strlen("export")) == 0)
			my_export(data, args);
		else if (ft_strncmp(args[0], "exit", ft_strlen("exit")) == 0)
			my_exit(data, args);
		exit(0);
	}
	init_parent_signals();
}

int	check_bild_fd(t_data *data, t_command *tmp_cmd)
{
	if (tmp_cmd->fd_out == -1 || tmp_cmd->fd_in == -1
		|| tmp_cmd->fd_hr_doc == -1)
	{
		perror(PROMT);
		data->status = 1;
		return (1);
	}
	return (0);
}

void	do_built(t_data *data, char **args, t_command *tmp_cmd)
{
	make_redir(data);
	if (data->pipe_num <= 0)
	{
		if (check_bild_fd(data, tmp_cmd))
			return ;
		if (ft_strncmp(args[0], "echo", ft_strlen("echo")) == 0)
			my_echo(args);
		else if (ft_strncmp(args[0], "cd", ft_strlen("cd")) == 0)
			my_cd(data, args);
		else if (ft_strncmp(args[0], "pwd", ft_strlen("pwd")) == 0)
			my_pwd();
		else if (ft_strncmp(args[0], "env", ft_strlen("env")) == 0)
			my_env(data);
		else if (ft_strncmp(args[0], "unset", ft_strlen("unset")) == 0)
			my_unset(data, args, 1);
		else if (ft_strncmp(args[0], "export", ft_strlen("export")) == 0)
			my_export(data, args);
		else if (ft_strncmp(args[0], "exit", ft_strlen("exit")) == 0)
			my_exit(data, args);
	}
	else
		fork_built(data, args, tmp_cmd);
}

int	check_err_print(t_data *data, char *ptr_to_eq, char *tmp)
{
	if (ptr_to_eq == tmp)
	{
		perr(0, 0, strerror(errno), 1);
		data->status = 1;
		return (1);
	}
	return (0);
}
