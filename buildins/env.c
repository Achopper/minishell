#include "minishell.h"

t_env	*make_env_node(t_data *data, char *str)
{
	char	*ptr_to_eq;
	t_env	*env_struc;
	char	*tmp;

	tmp = ft_strdup(str);
	ptr_to_eq = ft_strchr(tmp, '=');
	env_struc = (t_env *)malloc(sizeof(t_env));
	if (!env_struc || !tmp)
		error_exit(data, 1);
	if (check_err_print(data, ptr_to_eq, tmp))
		return (NULL);
	if (ptr_to_eq)
		*ptr_to_eq = '\0';
	env_struc->key = ft_strdup(tmp);
	if (ptr_to_eq)
		ptr_to_eq++;
	if (ptr_to_eq)
		env_struc->value = ft_strdup(ptr_to_eq);
	else
		env_struc->value = ft_strdup("");
	if (!env_struc->value || !env_struc->key)
		error_exit(data, 1);
	free(tmp);
	return (env_struc);
}

void	inc_shlvl(char **value_ptr)
{
	int	value;

	value = ft_atoi(*value_ptr);
	value++;
	free(*value_ptr);
	*value_ptr = ft_itoa(value);
}

char	*make_content(t_data *data, t_env *struc)
{
	char	*key;
	char	*value;
	char	*env_str;

	key = ft_strdup(struc->key);
	if (struc->value)
		value = ft_strdup(struc->value);
	else
		value = ft_strdup("");
	if (ft_strncmp(key, "SHLVL", ft_strlen(key)) == 0)
		inc_shlvl(&value);
	key = ft_strjoin(key, "=");
	env_str = ft_strjoin(key, value);
	if (!value || !key || !env_str)
		error_exit(data, 1);
	free(value);
	return (env_str);
}

void	make_env_arr(t_data *data)
{
	int		i;
	char	**tmp;
	t_list	*tmp_lst;

	i = 0;
	tmp_lst = data->env_lst;
	tmp = (char **)malloc(sizeof(char *) * (data->env_num + 1));
	if (!tmp)
		error_exit(data, 1);
	tmp[data->env_num] = NULL;
	while (tmp_lst && i < data->env_num)
	{
		tmp[i] = make_content(data, (t_env *)tmp_lst->content);
		tmp_lst = tmp_lst->next;
		i++;
	}
	if (data->env_arr)
		free_char_array(data->env_arr);
	data->env_arr = tmp;
}

void	get_env_lst(t_data *data)
{
	extern char	**environ;
	t_env		*env_struc;
	t_list		*new_list;
	int			i;

	i = 0;
	if (!environ)
		return ;
	while (environ[i])
	{
		env_struc = make_env_node(data, environ[i]);
		if (!env_struc)
			error_exit(data, 1);
		new_list = ft_lstnew((void *)env_struc);
		if (!new_list)
			error_exit(data, 1);
		ft_lstadd_back(&data->env_lst, new_list);
		i++;
	}
	data->env_num = i;
	make_env_arr(data);
}
