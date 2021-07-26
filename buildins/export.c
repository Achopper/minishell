#include "minishell.h"

void	swap(t_list *a, t_list *b)
{
	t_env	*temp;

	temp = a->content;
	a->content = b->content;
	b->content = temp;
}

void	bubbleSort(t_list *start, int swapped)
{
	t_list	*ptr1;
	t_list	*lptr;

	lptr = NULL;
	if (start == NULL)
		return ;
	while (swapped)
	{
		swapped = 0;
		ptr1 = start;
		while (ptr1 && ptr1->next != lptr)
		{
			while (ft_strncmp(((t_env *)ptr1->content)->key, \
			(((t_env *)(ptr1->next)->content)->key), \
			ft_strlen(((t_env *)ptr1->content)->key)) > 0)
			{
				swap(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}
}

t_env	*copy_lst_node(t_data *data, t_list *list)
{
	t_env	*env_struc;

	env_struc = (t_env *)malloc(sizeof(t_env));
	if (!env_struc)
		error_exit(data, 1);
	env_struc->key = ft_strdup(((t_env *)(list->content))->key);
	if (((t_env *)(list->content))->value && \
	*(((t_env *)(list->content))->value))
		env_struc->value = ft_strdup(((t_env *)(list->content))->value);
	else
		env_struc->value = ft_strdup("");
	if (!env_struc->value || !env_struc->key)
		error_exit(data, 1);
	return (env_struc);
}

t_list	*copy_env_lst(t_data *data)
{
	t_env	*env_struc;
	t_list	*res;
	t_list	*tmp;

	res = NULL;
	tmp = data->env_lst;
	while (tmp != NULL)
	{
		env_struc = copy_lst_node(data, tmp);
		if (!env_struc)
			error_exit(data, 1);
		else
			ft_lstadd_back(&res, ft_lstnew(env_struc));
		tmp = tmp->next;
	}
	return (res);
}

void	print_sorted_list(t_data *data)
{
	t_list	*tmp;

	data->env_sort_lst = copy_env_lst(data);
	bubbleSort(data->env_sort_lst, 1);
	tmp = data->env_sort_lst;
	while (tmp != NULL)
	{
		if (((t_env *)tmp->content)->value && \
			((t_env *)tmp->content)->value[0] != '\0')
			printf("declare -x %s=\"%s\"\n", ((t_env *)tmp->content)->key, \
			((t_env *)tmp->content)->value);
		else
			printf("declare -x %s\n", ((t_env *)tmp->content)->key);
		tmp = tmp->next;
	}
	while (data->env_sort_lst)
	{
		tmp = data->env_sort_lst->next;
		free(((t_env *)data->env_sort_lst->content)->value);
		free(((t_env *)data->env_sort_lst->content)->key);
		free(data->env_sort_lst->content);
		free(data->env_sort_lst);
		data->env_sort_lst = tmp;
	}	
}
