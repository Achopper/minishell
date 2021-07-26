#include "ast.h"

void	clean(t_btree *node)
{
	if (node)
		free(node);
}

void	clean_ast(t_btree *root, void (*clean)(t_btree *))
{
	if (root == NULL)
		return ;
	clean_ast(root->right, clean);
	clean_ast(root->left, clean);
	(*clean)(root);
}

void	btree_apply_prefix(t_btree *root, t_data **data, void (*applyf)
		(t_btree *, t_data **))
{
	if (root == NULL)
		return ;
	(*applyf)(root, data);
	btree_apply_prefix(root->right, data, applyf);
	btree_apply_prefix(root->left, data, applyf);
}

t_btree	*new_node(char *token, int type)
{
	t_btree	*new;

	new = (t_btree *)malloc(sizeof(t_btree));
	if (!new)
		exit(1);
	new->token = token;
	new->type = type;
	new->left = NULL;
	new->right = NULL;
	return (new);
}
