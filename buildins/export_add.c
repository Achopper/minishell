#include "minishell.h"

int	is_key_in_env_lst(t_data *data, t_env *env_struc)
{
	int		key_d_len;
	int		key_s_len;
	t_list	*tmp;

	tmp = data->env_lst;
	key_s_len = ft_strlen(env_struc->key);
	while (tmp)
	{
		key_d_len = ft_strlen(((t_env *)tmp->content)->key);
		if (!ft_strncmp(((t_env *)tmp->content)->key, env_struc->key, key_d_len) \
			&& (key_s_len == key_d_len))
		{
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	change_value(t_data *data, t_env *env_struc)
{
	int		key_d_len;
	int		key_s_len;
	t_list	*tmp;

	tmp = data->env_lst;
	key_s_len = ft_strlen(env_struc->key);
	while (tmp)
	{
		key_d_len = ft_strlen(((t_env *)tmp->content)->key);
		if (!ft_strncmp(((t_env *)tmp->content)->key, env_struc->key, key_d_len) \
		&& (key_s_len == key_d_len))
		{
			free(((t_env *)tmp->content)->value);
			((t_env *)tmp->content)->value = ft_strdup(env_struc->value);
			if (!((t_env *)tmp->content)->value)
				error_exit(data, 1);
			make_env_arr(data);
			return ;
		}
		tmp = tmp->next;
	}
}

void	add_node(t_data *data, t_env *env_struc)
{
	ft_lstadd_back(&data->env_lst, ft_lstnew((void *)env_struc));
	data->env_num++;
	make_env_arr(data);
}

t_env	*make_env_node2(t_data *data, char *arg, int eq_flag)
{
	t_env	*env_struc;
	char	*ptr;

	env_struc = (t_env *)malloc(sizeof(t_env));
	if (!env_struc)
		error_exit(data, 1);
	if (!eq_flag || (eq_flag && arg[0] == '='))
	{
		env_struc->key = ft_strdup(arg);
		env_struc->value = NULL;
	}
	else
	{
		ptr = ft_strchr(arg, '=');
		*ptr = '\0';
		env_struc->key = ft_strdup(arg);
		if (++ptr)
			env_struc->value = ft_strdup(ptr);
		else
			env_struc->value = ft_strdup("");
		if (!env_struc->key || !env_struc->value)
			error_exit(data, 1);
	}
	return (env_struc);
}

void	check_n_add_env(t_data *data, char **args, int i, int eq_flag)
{
	t_env	*env_struc;

	while (args[i])
	{
		eq_flag = have_eq(args[i]);
		env_struc = make_env_node2(data, args[i], eq_flag);
		if (!is_valid_key(env_struc->key))
		{
			perr(args[0], args[i], "not a valid identifier", 1);
			data->status = 1;
			free_struc(env_struc);
		}
		else
		{
			if (is_key_in_env_lst(data, env_struc))
			{
				if (eq_flag)
					change_value(data, env_struc);
				free_struc(env_struc);
			}
			else
				add_node(data, env_struc);
		}
		i++;
	}
}
