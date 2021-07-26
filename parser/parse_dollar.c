#include <string.h>
#include "parser.h"

char	*prep_env_token(char *input, char **environ)
{
	int		i;
	int		here_doc;
	char	*tmp;

	i = -1;
	tmp = NULL;
	here_doc = 0;
	while (input[++i])
	{
		check_here_doc(input, &i, &here_doc);
		if (input[i] == '$' && !here_doc)
		{
			if (input[i + 1] == '$' || input[i + 1] == ' ' || !input[i + 1])
				continue ;
			if (check_env(input, &i, environ) < 0 && input[i + 1] != '?')
			{
				tmp = del_doll_sign(input, &i);
				free(input);
				input = tmp;
				i = -1;
			}
		}
	}
	return (input);
}

char	*append_replace(char *input, char **environ, int env_no, const int
*index)
{
	int		env_len;
	int		in_len;
	char	*res;

	in_len = 0;
	env_len = (int)ft_strlen(environ[env_no]) - get_key_len(environ[env_no])
		- 1;
	get_after_doll_len(input, &in_len, *index);
	res = (char *)malloc(sizeof(char) * (ft_strlen(input) + env_len - in_len));
	if (!res)
	{
		ft_putstr_fd(ML_ERR, 2);
		exit(1);
	}
	ft_memmove(res, input, *index);
	ft_memmove(&res[*index], &environ[env_no][get_key_len(environ[env_no]) + 1],
		env_len);
	ft_memmove(&res[*index + env_len], &input[*index + in_len + 1],
		(ft_strlen(input) - in_len - *index));
	free(input);
	return (res);
}

char	*del_doll_sign(char *input, const int *index)
{
	char	*res;
	int		len_after_sign;

	len_after_sign = 0;
	get_after_doll_len(input, &len_after_sign, *index);
	res = (char *) malloc(sizeof(char) * (ft_strlen(input)
				- len_after_sign) + 1);
	if (!res)
	{
		ft_putstr_fd(ML_ERR, 2);
		exit(1);
	}
	res = ft_memmove(res, input, *index);
	ft_strlcpy(&res[*index], &input[*index + len_after_sign + 1],
		(ft_strlen(input) - *index - len_after_sign));
	return (res);
}

char	*put_exit_status(t_data *data, int *index)
{
	char	*res;
	char	*num;
	int		num_len;
	int		in_len;

	num = ft_itoa(data->status);
	num_len = (int)strlen(num);
	in_len = (int)strlen(data->input);
	res = (char *)malloc(sizeof(char) * (num_len + in_len - 2) + 1);
	if (!res)
		sys_err_exit(data, ML_ERR, 1);
	ft_memmove(res, data->input, *index);
	ft_memmove(&res[*index], num, num_len);
	ft_memmove(&res[*index + num_len],
		&data->input[*index + 2], in_len - *index + 2);
	res[num_len + in_len - 2] = '\0';
	free(data->input);
	free(num);
	return (res);
}

char	*replace_dollar_sign(t_data *data, char **environ, int *ind)
{
	int		i;
	int		env_no;

	i = *ind;
	while (data->input[i])
	{
		if (data->input[i] == '$')
		{
			if (data->input[i + 1] == '?')
			{
				data->input = put_exit_status(data, &i);
				data->status = 0;
				continue ;
			}
			env_no = check_env(data->input, &i, environ);
			if (env_no >= 0)
			{
				data->input = append_replace(data->input, environ, env_no, &i);
				break ;
			}
		}
		i++;
	}
	return (data->input);
}
