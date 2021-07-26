#ifndef AST_H
# define AST_H

# include "../../buildins/minishell.h"

typedef struct s_btree
{
	char			*token;
	int				type;
	struct s_btree	*left;
	struct s_btree	*right;
}					t_btree;

t_btree		*create_ast(t_token_list *token_list);
void		btree_apply_prefix(t_btree *root, t_data **data, void (*applyf)
				(t_btree *, t_data **));
int			make_comm_list(t_btree *root, t_data **data);
t_command	*new_com_node(char **args, int fd_in, int fd_out, int fd_here_doc);
void		push_back_comm_lst(t_command **begin, t_command *new);
void		clean_comm_lst(t_command *begin);
void		clean_ast(t_btree *root, void (*clean)(t_btree *));
void		clean(t_btree *node);
void		make_arg_buff(t_data **dt, t_btree *node);
void		get_all_fd(t_data **dt, t_btree *root);
void		close_fd(int *fd_out, int *fd_in, t_btree *root);
t_btree		*new_node(char *token, int type);
#endif
