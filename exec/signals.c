#include "../buildins/minishell.h"

void	cntr_d_handler(void)
{
	int	i;

	i = -1;
	tputs(cursor_up, 1, (int (*)(int)) ft_putchar);
	while (++i < (int)ft_strlen(PROMT))
		tputs(cursor_right, 1, (int (*)(int)) ft_putchar);
	write(1, "exit\n", 5);
	rl_redisplay();
	exit(0);
}

void	init_parent_signals(void)
{
	signal(SIGINT, int_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	ignore_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	set_signal_to_def(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	move_cursor_after_inp(int i)
{
	i = -1;
	while (++i < (int)ft_strlen(PROMT))
		tputs(cursor_right, 1, (int (*)(int)) ft_putchar);
	i = -1;
	while (++i < (int)ft_strlen(rl_line_buffer))
		tputs(cursor_right, 1, (int (*)(int)) ft_putchar);
	tputs(delete_character, 1, (int (*)(int)) ft_putchar);
	tputs(delete_character, 1, (int (*)(int)) ft_putchar);
}

//void	check_child_signal(int status)
//{
//	if (WTERMSIG(status) == SIGQUIT)
//		ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
//	if (WTERMSIG(status) == SIGINT)
//		ft_putstr_fd("\n", STDOUT_FILENO);
//}
