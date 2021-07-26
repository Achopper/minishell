#include "minishell.h"

t_env	*make_pwd_node(t_data *data)
{
	t_env	*pwd_node;
	char	*pwd_str;
	char	*pwd_str_start;
	char	buf[4096];
	char	*tmp_pwd;

	tmp_pwd = getcwd(buf, 4096);
	pwd_str_start = ft_strdup("PWD=");
	if (!tmp_pwd || !pwd_str_start)
		error_exit(data, 1);
	pwd_str = ft_strjoin(pwd_str_start, tmp_pwd);
	if (!pwd_str)
		error_exit(data, 1);
	pwd_node = make_env_node(data, pwd_str);
	if (!pwd_node)
		error_exit(data, 1);
	free(pwd_str);
	return (pwd_node);
}

t_env	*copy_struc(t_data *data, t_env *orig_struc)
{
	t_env	*new_struc;

	new_struc = malloc(sizeof(orig_struc));
	if (!new_struc)
		error_exit(data, 1);
	new_struc->key = ft_strdup(orig_struc->key);
	new_struc->value = ft_strdup(orig_struc->value);
	if (!new_struc->key || !new_struc->value)
		error_exit(data, 1);
	return (new_struc);
}

void	set_oldpwd(t_data *data, char *tmp_pwd)
{
	char	*oldpwd_str_start;
	t_env	*oldpwd_node;
	char	*oldpwd_str;

	if (!tmp_pwd)
		return ;
	oldpwd_str_start = ft_strdup("OLDPWD=");
	if (!oldpwd_str_start)
		error_exit(data, 1);
	oldpwd_str = ft_strjoin(oldpwd_str_start, tmp_pwd);
	if (!oldpwd_str)
		error_exit(data, 1);
	oldpwd_node = make_env_node(data, oldpwd_str);
	if (!oldpwd_node)
		error_exit(data, 1);
	if (is_key_in_env_lst(data, oldpwd_node))
		change_value(data, oldpwd_node);
	free_struc(oldpwd_node);
	free(oldpwd_str);
}

void	make_old_n_pwd(t_data *data, char *tmp_pwd)
{
	t_env	*pwd_node;

	pwd_node = make_pwd_node(data);
	if (is_key_in_env_lst(data, pwd_node))
		change_value(data, pwd_node);
	free_struc(pwd_node);
	set_oldpwd(data, tmp_pwd);
}

void	my_cd(t_data *data, char **args)
{
	int		res_cd;
	char	*newdir;
	char	*tmp_pwd;

	if (!args[1])
		return ;
	newdir = NULL;
	tmp_pwd = getcwd(0, 0);
	newdir = ft_strdup(args[1]);
	if (!newdir || !tmp_pwd)
	{
		data->status = 1;
		return ;
	}
	res_cd = chdir(newdir);
	if (res_cd == -1)
	{
		perr(args[0], 0, strerror(errno), 1);
		data->status = 1;
	}
	else
		make_old_n_pwd(data, tmp_pwd);
	free(tmp_pwd);
	free(newdir);
}
