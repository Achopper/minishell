#include "parser.h"

t_token_list	*new_tk_list(char *tk, int type)
{
	t_token_list	*new;

	new = (t_token_list *) malloc(sizeof(t_token_list));
	if (NULL == new)
		exit(1);
	new->lexeme = tk;
	new->token = type;
	new->next = NULL;
	return (new);
}

void	tk_list_add_back(t_token_list **tk_list, t_token_list *new)
{
	t_token_list	*tmp;

	if (!(*tk_list))
		*tk_list = new;
	else
	{
		tmp = *tk_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	tk_clear(t_token_list *tk_list)
{
	t_token_list	*tmp;

	tmp = NULL;
	if (tk_list->token != PIPE && tk_list->token != REDIR_OUT && tk_list->token
		!= D_REDIR_OUT && tk_list->token != REDIR_IN
		&& tk_list->token != HERE_DOC && tk_list->next == NULL)
	{
		free(tk_list->lexeme);
		free(tk_list);
		return ;
	}
	while (tk_list)
	{
		tmp = tk_list;
		tk_list = tk_list->next;
		if (tmp->token != PIPE && tmp->token != REDIR_OUT && tmp->token
			!= D_REDIR_OUT && tmp->token
			!= REDIR_IN && tmp->token != HERE_DOC)
			if (tmp->lexeme)
				free(tmp->lexeme);
		free(tmp);
	}
	free(tk_list);
}
