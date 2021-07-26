#include "buildins/minishell.h"

void	int_handler(int sig_num)
{
	int	i;

	i = -1;
	(void)sig_num;
	if (!rl_line_buffer)
	{
		while (++i < (int)ft_strlen(PROMT))
			tputs(cursor_right, 1, (int (*)(int)) ft_putchar);
		tputs(delete_character, 1, (int (*)(int)) ft_putchar);
		tputs(delete_character, 1, (int (*)(int)) ft_putchar);
	}
	if (rl_line_buffer)
		move_cursor_after_inp(i);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	init_struct(t_data *data)
{
	if (!data)
		sys_err_exit(data, ML_ERR, 1);
	ft_bzero(data, sizeof(t_data));
	init_parent_signals();
	get_env_lst(data);
	data->pid = 1;
}

void	clean_all(t_data **dt, t_token_list **tk_list, t_btree **tree)
{
	t_data			*data;
	t_token_list	*token_list;
	t_btree			*ast;

	data = *dt;
	token_list = *tk_list;
	ast = *tree;
	if (data->comm_lst)
	{
		clean_comm_lst(data->comm_lst);
		data->comm_lst = NULL;
		*dt = data;
	}
	clean_ast(ast, (clean));
	if (token_list)
	{
		tk_clear(token_list);
		token_list = NULL;
		*tk_list = token_list;
	}
	*tree = ast;
}

void	do_readline(t_data *data)
{
	data->redir_err = NULL;
	if (data->input)
		free(data->input);
	data->input = readline(PROMT);
	if (!data->input && data->pid != 0)
		cntr_d_handler();
	else if (data->input && *data->input)
	{
		add_history(data->input);
		rl_replace_line("", 0);
		rl_redisplay();
		rl_on_new_line();
	}
	else if (data->input[0] == 0)
		return ;
}

int	main(void)
{
	t_data	*data;
	t_btree	*ast;

	data = (t_data *)malloc(sizeof(t_data));
	init_struct(data);
	while (1)
	{
		data->pipe_num = 0;
		data->word_num = 0;
		do_readline(data);
		if (data->input[0] == 0)
			continue ;
		if (parser(data, &data->token_list) > 0)
		{
			ft_putstr_fd(PIPE_RED_ER, STDERR_FILENO);
			tk_clear(data->token_list);
			data->token_list = NULL;
			continue ;
		}
		ast = create_ast(data->token_list);
		make_comm_list(ast, &data);
		exec(data, 0);
		clean_all(&data, &data->token_list, &ast);
	}
}
