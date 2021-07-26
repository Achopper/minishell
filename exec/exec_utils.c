#include "../buildins/minishell.h"

char	*get_value_by_key(t_data *data, char *key)
{
	int		key_d_len;
	int		key_s_len;
	t_list	*tmp;

	tmp = data->env_lst;
	key_s_len = ft_strlen(key);
	while (tmp)
	{
		key_d_len = ft_strlen(((t_env *)tmp->content)->key);
		if (!ft_strncmp(((t_env *)tmp->content)->key, key, \
			key_d_len) && (key_s_len == key_d_len))
		{
			if (((t_env *)tmp->content)->value)
				return (ft_strdup(((t_env *)tmp->content)->value));
			else
				return (NULL);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int	perr(char *cmd, char *arg, char *err, int code)
{
	ft_putstr_fd("minishell", STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (cmd)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (arg)
	{
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (err)
		ft_putstr_fd(err, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (code);
}

int	is_dir(char *path)
{
	struct stat	sb;

	if (stat(path, &sb) == -1)
		return (0);
	if ((sb.st_mode & S_IFMT) == S_IFDIR)
		return (1);
	return (0);
}

int	check_cmd(char *arg)
{
	if (ft_strrchr(arg, '/'))
	{
		return (1);
	}
	return (0);
}

void 	check_fd(t_command *tmp_cmd, char **args)
{
	if ((tmp_cmd->fd_out == -1 || tmp_cmd->fd_in == -1
			|| tmp_cmd->fd_hr_doc == -1))
		exit(perr(args[0], 0, strerror(errno), 1));
}
