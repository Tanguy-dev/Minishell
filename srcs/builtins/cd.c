/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamon <thamon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 18:39:02 by thamon            #+#    #+#             */
/*   Updated: 2022/02/02 18:41:12 by thamon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	show_error(char **args)
{
	ft_putstr_fd("cd: ", STDERR);
	if (args[2])
		ft_putstr_fd("string not in pwd: ", STDERR);
	else
	{
		ft_putstr_fd(strerror(errno), STDERR);
		ft_putstr_fd(": ", STDERR);
	}
	ft_putendl_fd(args[1], STDERR);
}

int	update_oldpath(t_env *env)
{
	char	pwd[PATH_MAX];
	char	*old_pwd;

	if (getcwd(pwd, PATH_MAX) == NULL)
		return (1);
	old_pwd = ft_strjoin("OLDPWD=", pwd);
	if (in_env(old_pwd, env) == 0)
		env_add(old_pwd, env);
	ft_memdel(old_pwd);
	return (0);
}

static int	update_path(t_env *env)
{
	char	pwd[PATH_MAX];
	char	*new;

	if (getcwd(pwd, PATH_MAX) == NULL)
		return (1);
	new = ft_strjoin("PWD=", pwd);
	while (ft_strncmp(env->value, "PWD=", 4))
		env = env->next;
	env->value = new;
	return (0);
}

static int	path(int option, t_env *env)
{
	int		ret;
	char	*env_path;

	env_path = NULL;
	if (option == 0)
	{
		update_oldpath(env);
		env_path = get_path(env, "HOME", 4);
		if (!env_path)
			ft_putendl_fd("minishell: cd: HOME not set", STDERR);
		if (!env_path)
			return (1);
	}
	else if (option == 1)
	{
		env_path = path2(env_path, env);
		if (!env_path)
			return (1);
		update_oldpath(env);
	}
	ret = chdir(env_path);
	update_path(env);
	ft_memdel(env_path);
	return (ret);
}

int	mini_cd(char **args, t_env *env)
{
	int	ret;

	if (args[1] == NULL)
		return (path(0, env));
	if (ft_strcmp(args[1], "-") == 0)
	{
		ret = path(1, env);
		mini_pwd(env);
	}
	else
	{
		update_oldpath(env);
		ret = chdir(args[1]);
		update_path(env);
		if (ret < 0)
			ret *= -1;
		if (ret != 0)
			show_error(args);
	}
	return (ret);
}
