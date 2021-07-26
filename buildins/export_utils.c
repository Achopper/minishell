#include "minishell.h"

void	free_struc(t_env *env_struc)
{
	free(env_struc->value);
	free(env_struc->key);
	free(env_struc);
}

int	have_eq(char *str)
{
	char	*ptr_to_eq;

	ptr_to_eq = ft_strchr(str, '=');
	if (ptr_to_eq)
		return (1);
	return (0);
}

int	is_valid_key(char *s)
{
	int	i;

	if (!s || ft_memcmp(s, "\0", 1) == 0)
		return (0);
	i = 0;
	while (s[i])
	{
		if (i == 0 && ft_isdigit(s[i]))
			return (0);
		if (!(ft_strchr("_", s[i]) || ft_isalnum(s[i])))
			return (0);
		i++;
	}
	return (1);
}
