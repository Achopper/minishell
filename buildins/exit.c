#include "minishell.h"

int	is_digits_only(const char *s)
{
	if (ft_strlen(s) > 18)
		return (0);
	if (!ft_isdigit(*s) && ft_strlen(s) == 1)
		return (0);
	if (!(*s == '+' || *s == '-' || ft_isdigit(*s)))
		return (0);
	s++;
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (0);
		s++;
	}
	return (1);
}

void	my_exit(t_data *data, char **args)
{
	(void)data;
	if (!args[1])
		exit(0);
	if (args[2])
	{
		perr(args[0], 0, "too many arguments", 1);
		data->status = 1;
		return ;
	}
	if (!is_digits_only(args[1]))
	{
		perr(args[0], args[1], "numeric argument required", 255);
		data->status = 255;
		exit(255);
	}
	else
		exit((unsigned int)ft_atoi(args[1]));
}
