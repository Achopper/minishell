#ifndef PARSER_H
# define PARSER_H

# include "../libft/libft.h"
# include <stdio.h>

# define WORD 0
# define PIPE 7
# define REDIR_IN 3
# define HERE_DOC 4
# define REDIR_OUT 5
# define D_REDIR_OUT 6
# define ML_ERR "Malloc error\n"
# define FRK_ERR "Fork err\n"
# define QT_ERR "Minishell not support multiline\n"
# define PIPE_RED_ER  "syntax REDIRECT or PIPE error\n"

typedef struct s_command
{
	char				**args;
	int					fd_in;
	int					fd_out;
	int					fd_hr_doc;
	struct s_command	*next;
}						t_command;

typedef struct s_token_list
{
	char						*lexeme;
	int							token;
	struct s_token_list			*next;
}								t_token_list;

typedef struct s_data
{
	pid_t			pid;
	t_token_list	*token_list;
	int				status;
	char			*input;
	int				fd0;
	int				fd1;
	int				redir_fd0;
	int				redir_fd1;
	int				pipe[2];
	int				env_num;
	t_list			*env_lst;
	t_list			*env_sort_lst;
	char			**env_arr;
	t_command		*comm_lst;
	t_command		*tmp;
	int				pipe_num;
	int				word_num;
	char			**buf;
	char			*redir_err;
	int				err;
}					t_data;

int				parser(t_data *data, t_token_list **token_list);
void			check_redirect(char *input, int *index, t_token_list
					**token_list);
int				check_type(t_token_list *tk_list, t_data *data);
int				get_token_len(t_data *data, int *index);
char			*prep_env_token(char *input, char **environ);
int				check_env(const char *input, const int *index, char **environ);
int				get_key_len(const char *env);
char			*del_doll_sign(char *input, const int *index);
char			*get_quote_token(t_data *data, int *index, char quot_type);
char			*check_next_quote(t_data *data, char *end, char *res, int
					*index);
void			check_quote_type(t_data **dt, int double_quote, int i);
void			check_here_doc(char *input, int *index, int *flag);
char			*get_token(t_data *data, int *index);
char			*replace_dollar_sign(t_data *data, char **environ, int *ind);
void			get_after_doll_len(char *input, int *len, int index);
void			sys_err_exit(t_data *data, char *err_msg, int code);

t_token_list	*new_tk_list(char *tk, int type);
void			tk_clear(t_token_list *tk_list);
void			tk_list_add_back(t_token_list **tk_list, t_token_list *new);

#endif
