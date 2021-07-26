#include "../buildins/minishell.h"

int	get_key_len(const char *env)
{
	int	i;

	i = -1;
	if (!env)
	{
		ft_putstr_fd("error in env", STDERR_FILENO);
		exit(1);
	}
	while (env[++i] != '=')
		;
	return (i);
}

void	check_here_doc(char *input, int *index, int *flag)
{
	if (input[*index] == '<' && input[*index + 1] == '<' )
		*flag = 1;
	if (*flag)
	{
		*index += 2;
		while (!ft_isalnum(input[*index]))
			*index += 1;
		while (ft_isprint(input[*index]))
			*index += 1;
		*index -= 1;
	}
	flag = 0;
}

void	check_quote_type(t_data **dt, int double_quote, int i)
{
	t_data	*data;
	int		here_doc;

	data = *dt;
	here_doc = 0;
	while (data->input[++i])
	{
		check_here_doc(data->input, &i, &here_doc);
		if (data->input[i] == '\'' && !double_quote)
			while (data->input[++i] != '\'' && data->input[i])
				++i;
		if (data->input[i] == '$' && !here_doc)
			data->input = replace_dollar_sign(data, data->env_arr, &i);
		if (data->input[i] == '\"' && !double_quote)
		{
			double_quote = 1;
			continue ;
		}
		if (data->input[i] == '\"' && double_quote)
			double_quote = 0;
	}
}

void	check_redirect(char *input, int *index, t_token_list **token_list)
{
	if (input[*index] == '<' && input[*index + 1] != '<')
	{
		tk_list_add_back(token_list, new_tk_list("RD_IN", REDIR_IN));
		return ;
	}
	else if (input[*index] == '<' && input[*index + 1] == '<')
	{
		tk_list_add_back(token_list, new_tk_list("HERE_DOC", HERE_DOC));
		*index += 1;
		return ;
	}
	else if (input[*index] == '>' && input[*index + 1] != '>')
	{
		tk_list_add_back(token_list, new_tk_list("RD_OUT", REDIR_OUT));
		return ;
	}
	else if (input[*index] == '>' && input[*index + 1] == '>')
	{
		tk_list_add_back(token_list, new_tk_list("D_RD_OUT", D_REDIR_OUT));
		*index += 1;
		return ;
	}
}

void 	get_after_doll_len(char *input, int *len, int index)
{
	int	i;

	i = index + 1;
	if (ft_isdigit(input[i]))
	{
		*len += 1;
		return ;
	}
	while (ft_isprint(input[i]) && input[i] != '\'' && input[i] != '\"')
	{
		if (input[i] == '$' || ft_isspace(input[i]) || !ft_isalnum(input[i]))
			break ;
		*len += 1;
		i++;
	}
}
