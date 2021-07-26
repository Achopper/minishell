#include "ast.h"

void	insert_above(t_btree **res, t_btree **node_to_ins)
{
	t_btree	*res_ptr;
	t_btree	*node_to_ins_ptr;

	res_ptr = *res;
	node_to_ins_ptr = *node_to_ins;
	node_to_ins_ptr->right = res_ptr;
	res_ptr = node_to_ins_ptr;
	*res = res_ptr;
}

t_btree	*insert_bt_node(t_btree *root, t_btree *node_to_ins)
{
	t_btree	*res;

	if (!root)
		return (node_to_ins);
	res = root;
	if (res->type < node_to_ins->type)
		if (res->type >= REDIR_IN && node_to_ins->type >= REDIR_IN
			&& node_to_ins->type != PIPE)
			res->right = insert_bt_node(res->right, node_to_ins);
	else
		insert_above(&res, &node_to_ins);
	else if (res->type > node_to_ins->type && res->type != PIPE)
		res->right = insert_bt_node(res->right, node_to_ins);
	else if (res->type == node_to_ins->type)
		if (node_to_ins->type == PIPE)
			insert_above(&res, &node_to_ins);
	else
		res->right = insert_bt_node(res->right, node_to_ins);
	else if (res->type == PIPE)
		res->left = insert_bt_node(res->left, node_to_ins);
	return (res);
}

t_btree	*create_ast(t_token_list *token_list)
{
	t_btree	*res;
	t_btree	*node;

	res = NULL;
	node = NULL;
	while (token_list)
	{
		node = new_node(token_list->lexeme, token_list->token);
		if (token_list->token >= REDIR_IN && token_list->token != PIPE)
		{
			free(node);
			node = new_node(token_list->next->lexeme, token_list->token);
			token_list = token_list->next;
		}
		res = insert_bt_node(res, node);
		token_list = token_list->next;
		node = NULL;
	}
	return (res);
}
