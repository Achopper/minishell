#include "../buildins/minishell.h"

void	here_doc_int(int sig_num)
{
	if (sig_num == SIGINT)
	{
		open("tmp.txt", O_TRUNC | O_CLOEXEC, 0666);
		exit(1);
	}
}

void	do_child_here_doc(t_data *data, t_btree *root, char *here_doc)
{
	set_signal_to_def();
	data->tmp->fd_hr_doc = open("tmp.txt", O_CREAT | O_WRONLY
			| O_TRUNC | O_CLOEXEC, 0666);
	signal(SIGINT, here_doc_int);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		here_doc = NULL;
		here_doc = readline(HERE_DOC_PROMT);
		if (!here_doc)
		{
			tputs(cursor_up, 1, (int (*)(int)) ft_putchar);
			rl_on_new_line();
			rl_replace_line("", 0);
			free(here_doc);
			break ;
		}
		if (ft_memcmp(here_doc, root->token, ft_strlen(root->token))
			== 0 && ft_strlen(root->token) == ft_strlen(here_doc))
			break ;
		here_doc[ft_strlen(here_doc)] = '\n';
		write(data->tmp->fd_hr_doc, here_doc, ft_strlen(here_doc));
		free(here_doc);
	}
}

void	do_here_doc(t_data *data, t_btree *root, char *here_doc)
{
	pid_t	pid;

	pid = fork();
	ignore_signals();
	if (pid == 0)
	{
		do_child_here_doc(data, root, here_doc);
		exit(0);
	}
	waitpid(pid, NULL, 0);
	init_parent_signals();
	data->tmp->fd_in = open("tmp.txt", O_RDONLY);
}

void	read_from_fd(t_data *data, t_btree *root)
{
	char	*here_doc;

	here_doc = NULL;
	if (root->type == REDIR_IN)
	{
		data->tmp->fd_in = open(root->token, O_RDONLY | O_EXCL);
		if (data->tmp->fd_in == -1)
		{
			data->redir_err = root->token;
			data->err = errno;
		}
	}
	else
		do_here_doc(data, root, here_doc);
}

void	get_all_fd(t_data **dt, t_btree *root)
{
	t_data	*data;

	data = *dt;
	if ((root->type == REDIR_IN || root->type == HERE_DOC))
		read_from_fd(data, root);
	else if ((root->type == REDIR_OUT || root->type == D_REDIR_OUT)
		&& !data->redir_err)
	{
		if (root->type == REDIR_OUT)
			data->tmp->fd_out = open(root->token, O_CREAT | O_WRONLY | O_TRUNC,
					0666);
		else
			data->tmp->fd_out = open(root->token, O_CREAT | O_WRONLY | O_APPEND,
					0666);
	}
	if (root->right)
		if (root->right->type >= REDIR_IN)
			close_fd(&data->tmp->fd_out, &data->tmp->fd_in, root);
}
