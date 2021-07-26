#include "../buildins/minishell.h"

void	clean_comm_lst(t_command *begin)
{
	t_command	*tmp;

	close(begin->fd_in);
	close(begin->fd_out);
	unlink("tmp.txt");
	if (begin->next == NULL)
	{
		free_char_array(begin->args);
		free(begin);
		begin = NULL;
		return ;
	}
	while (begin)
	{
		tmp = begin;
		begin = begin->next;
		free_char_array(tmp->args);
		free(tmp);
	}
	free(begin);
	begin = NULL;
}

t_command	*new_com_node(char **args, int fd_in, int fd_out, int fd_here_doc)
{
	t_command	*new;
	int			i;

	i = -1;
	new = (t_command *)malloc(sizeof(t_command));
	if (!new)
		exit(1);
	while (args[++i])
		;
	new->args = ft_calloc((int)(i + 1), sizeof(new->args));
	i = -1;
	while (args[++i])
		new->args[i] = ft_strdup(args[i]);
	new->fd_in = fd_in;
	new->fd_out = fd_out;
	new->fd_hr_doc = fd_here_doc;
	new->next = NULL;
	return (new);
}

void	push_back_comm_lst(t_command **begin, t_command *new)
{
	t_command	*tmp;

	if (!*(begin))
		*(begin) = new;
	else
	{
		tmp = *begin;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	make_arg_buff(t_data **dt, t_btree *node)
{
	t_data	*data;
	int		i;

	i = -1;
	data = NULL;
	data = *dt;
	if (!data->buf[0])
	{
		data->buf[0] = ft_strdup(node->token);
		if (!data->buf[0])
			sys_err_exit(data, ML_ERR, 1);
	}
	else
	{
		while (data->buf[++i])
			;
		data->buf[i] = ft_strdup(node->token);
		if (!data->buf[i])
			sys_err_exit(data, ML_ERR, 1);
	}
}

void	close_fd(int *fd_out, int *fd_in, t_btree *root)
{
	if (root->right->type == REDIR_IN || root->right->type == HERE_DOC)
		if (*fd_in > 1)
			close(*fd_in);
	if (root->right->type == REDIR_OUT || root->right->type == D_REDIR_OUT)
		if (*fd_out > 1)
			close(*fd_out);
}
