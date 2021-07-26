#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/stat.h>
# include <term.h>
# include <termios.h>
# include <errno.h>

# include "../parser/parser.h"
# include "../parser/ast/ast.h"

# define PROMT 			"minishell-> "
# define HERE_DOC_PROMT 	"> "

typedef struct s_env
{
	char	*key;
	char	*value;
}				t_env;

void		do_built(t_data *data, char **cmd, t_command *tmp_cmd);
void		get_env_lst(t_data *data);
int			is_built(char *arg);
void		free_lst_struc(t_data *data, t_list *env_lst);
// t_env		*make_env_node(t_data *data, char *str, int eq_flag);
t_env		*make_env_node(t_data *data, char *str);
void		print_sorted_list(t_data *data);
int			error_exit(t_data *data, int code);
void		sys_err_exit(t_data *data, char *err_msg, int code);
void		check_n_add_env(t_data *data, char **args, int i, int eq_flag);
int			is_key_in_env_lst(t_data *data, t_env *env_struc);
void		change_value(t_data *data, t_env *env_struc);
void		add_node(t_data *data, t_env *env_struc);
void		free_struc(t_env *env_struc);
t_env		*copy_lst_node(t_data *data, t_list *list);
t_env		*copy_struc(t_data *data, t_env *orig_struc);
void		my_env(t_data *data);
void		my_pwd(void);
void		my_echo(char **args);
void		my_cd(t_data *data, char **args);
void		my_exit(t_data *data, char **args);
void		my_unset(t_data *data, char **args, int j);
void		my_export(t_data *data, char **args);
void		make_env_arr(t_data *data);
void		create_pipe_redir_fd1(t_data *data, int i);
void		save_fds(t_data *data);
void		create_pipe_redir_fd1(t_data *data, int i);
void		close_child_fds(t_data *data);
void		redir_fd0_close_pipe(t_data *data);
void		restore_fds(t_data *data);
int			is_valid_key(char *s);
int			perr(char *cmd, char *arg, char *err, int code);
char		*get_value_by_key(t_data *data, char *key);
int			is_dir(char *path);
int			check_cmd(char *arg);
void		check_fd(t_command *tmp_cmd, char **args);
void		free_struc(t_env *env_struc);
int			have_eq(char *str);
void		make_redir(t_data *data);
int			check_err_print(t_data *data, char *ptr_to_eq, char *tmp);
char		*get_binary(t_data *data, char **args, int i);
int			check_bild_fd(t_data *data, t_command *tmp_cmd);

void		cntr_d_handler(void);
void		int_handler(int sig_num);
void		init_parent_signals(void);
void		exec(t_data *data, int i);
void		ignore_signals(void);
void		set_signal_to_def(void);
void		move_cursor_after_inp(int i);
void		check_child_signal(int status);

extern void	rl_replace_line(const char *text, int clear_undo);

#endif