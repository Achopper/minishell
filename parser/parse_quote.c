#include "parser.h"

char 	*find_quote_pos(t_data *data, int *index, char q_t, char **start)
{
	char	*end;

	while (data->input[*index])
	{
		if (data->input[*index] == q_t)
		{
			*index += 1;
			*start = &data->input[*index];
			break ;
		}
	}
	end = ft_strchr(*start, q_t);
	if (!end)
		sys_err_exit(data, QT_ERR, 1);
	return (end);
}

char	*get_next_token_if(t_data *data, int *index, char **result)
{
	char	*tmp;

	*index += 1;
	tmp = get_token(data, index);
	*result = ft_strjoin(*result, tmp);
	if (!*result)
		sys_err_exit(data, ML_ERR, 1);
	if (tmp)
		free(tmp);
	return (*result);
}

char	*get_quote_token(t_data *data, int *index, char quot_type)
{
	char	*result;
	char	*start;
	char	*end;

	start = NULL;
	end = find_quote_pos(data, index, quot_type, &start);
	result = ft_substr(data->input, *index, end - start);
	if (!result)
		sys_err_exit(data, ML_ERR, 1);
	*index += (int)(end - start);
	result = check_next_quote(data, end, result, index);
	if (ft_isprint(*(end + 1)) && !ft_strchr(" \'\"|<>", *(end + 1)))
		get_next_token_if(data, index, &result);
	return (result);
}

char	*check_next_quote(t_data *data, char *end, char *res, int *index)
{
	char	*tmp;
	char	q_t;

	q_t = 0;
	if (*(end + 1) == '\"' || *(end + 1) == '\'')
	{
		if (*(end + 1) == '\"')
			q_t = '\"';
		if (*(end + 1) == '\'')
			q_t = '\'';
		*index += 1;
		tmp = get_quote_token(data, index, q_t);
		res = ft_strjoin(res, tmp);
		free(tmp);
		if (!res)
			sys_err_exit(data, ML_ERR, 1);
	}
	return (res);
}
