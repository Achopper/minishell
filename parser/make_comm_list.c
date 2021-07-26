#include "../buildins/minishell.h"

void	get_comm_lst(t_data *data)
{
	int	i;

	i = -1;
	while (data->buf[++i])
		;
	data->tmp->args = ft_calloc((int)(i + 1), sizeof(data->tmp->args));
	if (!data->tmp->args)
		sys_err_exit(data, ML_ERR, 1);
	i = -1;
	while (data->buf[++i])
	{
		data->tmp->args[i] = ft_strdup(data->buf[i]);
		if (!data->tmp->args[i])
			sys_err_exit(data, ML_ERR, 1);
	}
	push_back_comm_lst(&data->comm_lst, new_com_node(data->tmp->args,
			data->tmp->fd_in, data->tmp->fd_out, data->tmp->fd_hr_doc));
	free_char_array(data->buf);
	data->tmp->fd_hr_doc = -2;
	data->tmp->fd_in = -2;
	data->tmp->fd_out = -2;
	free_char_array(data->tmp->args);
	data->buf = ft_calloc((int)(data->word_num + 1), sizeof(char **));
}

void	apply_node(t_btree *root, t_data **data)
{
	t_data	*dt;

	dt = *data;
	if (root->type == WORD)
	{
		make_arg_buff(&dt, root);
		if (!dt->buf)
			sys_err_exit(dt, ML_ERR, 1);
	}
	else if (root->type >= REDIR_IN && root->type != PIPE)
		get_all_fd(&dt, root);
	if (root->right == NULL)
		get_comm_lst(dt);
}

int	make_comm_list(t_btree *root, t_data **dt)
{
	t_data	*data;

	data = *dt;
	data->tmp = (t_command *)malloc(sizeof(t_command));
	if (!data->tmp)
		sys_err_exit(data, ML_ERR, 1);
	data->tmp->fd_hr_doc = -2;
	data->tmp->fd_in = -2;
	data->tmp->fd_out = -2;
	data->buf = ft_calloc((int)(data->word_num + 1), sizeof(char **));
	if (!data->buf)
		sys_err_exit(data, ML_ERR, 1);
	btree_apply_prefix(root, dt, apply_node);
	free_char_array(data->buf);
	free(data->tmp);
	return (0);
}
