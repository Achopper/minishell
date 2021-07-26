#include "parser.h"

char	*get_token(t_data *data, int *index)
{
	char	*res;
	char	*tmp;
	int		len;

	len = get_token_len(data, index);
	res = ft_substr(data->input, *index, len);
	if (!res)
		sys_err_exit(data, ML_ERR, 1);
	*index += len;
	if (data->input[*index] == '\'' || data->input[*index] == '\"')
	{
		tmp = get_quote_token(data, index, data->input[*index]);
		res = ft_strjoin(res, tmp);
		if (!res)
			sys_err_exit(data, ML_ERR, 1);
		if (tmp)
			free(tmp);
	}
	return (res);
}

void	get_word_or_pipe_token(t_data *data, t_token_list **token_list, int *i)
{
	if (ft_isprint(data->input[*i]) && !ft_strchr(" \'\"|<>", data->input[*i]))
	{
		tk_list_add_back(token_list, new_tk_list(get_token(data, i), WORD));
		return ;
	}
	if (data->input[*i] == '\'' || data->input[*i] == '\"')
	{
		tk_list_add_back(token_list, new_tk_list(get_quote_token(data, i,
					data->input[*i]), WORD));
		return ;
	}
}

char	*prep_input(t_data *data)
{
	int	d_q;
	int	i;

	d_q = 0;
	i = -1;
	check_quote_type(&data, d_q, i);
	return (data->input);
}

void	parse_input(t_data *data, t_token_list **token_list,
					int *index, int len)
{
	while (++*(index) < len)
	{
		if ((data->input[*(index)] == '$' && data->input[*(index) + 1] == '\'')
			|| (data->input[*(index)] == '$'
				&& data->input[*(index) + 1] == '\"'))
			continue ;
		get_word_or_pipe_token(data, token_list, index);
		check_redirect(data->input, index, token_list);
		if (data->input[*index] == '|')
			tk_list_add_back(token_list, new_tk_list("PIPE", PIPE));
	}
}

int	parser(t_data *data, t_token_list **token_list)
{
	int	i;
	int	len;

	i = -1;
	len = 0;
	if (data->input)
	{
		data->input = prep_env_token(data->input, data->env_arr);
		data->input = prep_input(data);
		len = (int) ft_strlen(data->input);
	}
	parse_input(data, token_list, &i, len);
	return (check_type(*token_list, data));
}
