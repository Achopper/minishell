#include "../buildins/minishell.h"

char	*check_path(char **splited, char *env, t_data *data, char **args)
{
	struct stat	buf;
	char		*res;
	int			i;

	i = -1;
	while (splited[++i])
	{
		splited[i] = ft_strjoin(splited[i], "/");
		splited[i] = ft_strjoin(splited[i], args[0]);
		if (!splited[i])
			sys_err_exit(data, ML_ERR, 1);
		if (stat(splited[i], &buf) == 0)
		{
			res = ft_strdup(splited[i]);
			if (!res)
				sys_err_exit(data, ML_ERR, 1);
			free_char_array(splited);
			free(env);
			return (res);
		}
	}
	free_char_array(splited);
	free(env);
	return (0);
}

char	*get_binary(t_data *data, char **args, int i)
{
	char		**splited;
	char		*env;
	int			is_cmd;

	i = 0;
	if (!args || ft_memcmp(args[0], "\0", 1) == 0)
		return (0);
	is_cmd = check_cmd(args[0]);
	if (is_cmd)
		return (ft_strdup(args[0]));
	env = get_value_by_key(data, "PATH");
	if (!env)
		return (0);
	splited = ft_split(env, ':');
	if (!splited)
		sys_err_exit(data, ML_ERR, 1);
	return (check_path(splited, env, data, args));
}
