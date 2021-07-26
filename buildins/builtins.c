#include "minishell.h"

void	my_pwd(void)
{
	char	*s;

	s = getcwd(0, 0);
	if (!s)
		return ;
	write(1, s, ft_strlen(s));
	write(1, "\n", ft_strlen("\n"));
	free(s);
}

void	find_n_remove_var(t_data *data, t_list	*tmp, char *arg)
{
	t_list	*prev;

	prev = 0;
	while (tmp)
	{
		if (!(ft_strncmp(((t_env *)(tmp->content))->key, arg, \
			ft_strlen(((t_env *)(tmp->content))->key))) && \
			ft_strlen(((t_env *)(tmp->content))->key) == ft_strlen(arg))
		{
			if (prev)
				prev->next = tmp->next;
			else
				data->env_lst = tmp->next;
			free_struc(tmp->content);
			free(tmp);
			data->env_num--;
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

void	my_unset(t_data *data, char **args, int j)
{
	t_list	*tmp;

	if (!args[1] || !data->env_lst)
		return ;
	while (args[j])
	{
		if (!is_valid_key(args[j]))
		{
			perr(args[0], args[j], "not a valid identifier", 1);
			return ;
		}
		tmp = data->env_lst;
		find_n_remove_var(data, tmp, args[j]);
		j++;
	}
	make_env_arr(data);
}

void	my_export(t_data *data, char **args)
{
	if (!args[1])
		print_sorted_list(data);
	else
	{
		check_n_add_env(data, args, 1, 0);
	}
}

void	my_env(t_data *data)
{
	int			i;
	t_env		*env_struc;
	t_list		*tmp;

	tmp = NULL;
	i = 0;
	tmp = data->env_lst;
	while (i < data->env_num)
	{
		env_struc = tmp->content;
		if (((t_env *)tmp->content)->value)
			printf("%s=%s\n", env_struc->key, env_struc->value);
		tmp = tmp->next;
		i++;
	}
}
