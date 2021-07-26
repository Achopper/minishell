#include "parser.h"

int	check_type(t_token_list *tk_list, t_data *data)
{
	if (tk_list)
	{
		if (tk_list->token == PIPE)
			return (1);
		while (tk_list->next != NULL)
		{
			if (tk_list->token == PIPE)
				data->pipe_num++;
			if (tk_list->token == WORD)
				data->word_num++;
			if (tk_list->token == PIPE && tk_list->next->token == PIPE)
				return (1);
			if (tk_list->token >= REDIR_IN && tk_list->next->token != WORD
				&& tk_list->token != PIPE)
				return (1);
			tk_list = tk_list->next;
		}
		if (tk_list->token == WORD)
			data->word_num++;
		if ((tk_list->token >= REDIR_IN && !tk_list->next)
			|| (tk_list->token == PIPE && !tk_list->next))
			return (1);
	}
	return (0);
}

int	get_token_len(t_data *data, int *index)
{
	int	i;
	int	len;

	i = *index;
	len = 0;
	while (data->input[i] && !ft_strchr(" |<>\'\"", data->input[i]))
	{
		len++;
		i++;
	}
	return (len);
}

int	check_env(const char *input, const int *index, char **environ)
{
	int	len;
	int	i;
	int	j;

	i = *index + 1;
	len = 0;
	j = -1;
	while (ft_isalnum(input[i]) && input[i] != '\0')
	{
		len++;
		i++;
	}
	i = *index + 1;
	while (environ[++j])
	{
		if (ft_strncmp(&input[i], environ[j], len) == 0
			&& len == get_key_len(environ[j]))
			return (j);
	}
	return (-1);
}
