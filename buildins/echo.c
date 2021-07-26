#include "minishell.h"

int	is_n_opt(char *arg)
{
	int	i;

	i = 2;
	if (arg && ft_strlen(arg) >= 2 && ft_strncmp(arg, "-n", 2) == 0)
	{
		while (arg[i] && arg[i] == 'n')
			i++;
		if (i == (int)ft_strlen(arg))
			return (1);
	}
	return (0);
}

void	my_echo(char **args)
{
	int	i;
	int	was_n_opt;

	i = 1;
	was_n_opt = 0;
	while (is_n_opt(args[i]))
	{
		was_n_opt = 1;
		i++;
	}
	while (args[i])
	{
		write(1, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!was_n_opt)
		write(1, "\n", 1);
}
