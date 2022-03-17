/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamon <thamon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 18:39:12 by thamon            #+#    #+#             */
/*   Updated: 2022/03/17 15:20:57 by jusaint-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_add(char *value, t_env *env)
{
	t_env	*new;
	t_env	*tmp;

	if (env && env->value == NULL)
	{
		env->value = ft_strdup(value);
		return (0);
	}
	new = malloc(sizeof(t_env));
	new->value = ft_strdup(value);
	while (env && env->next && env->next->next)
		env = env->next;
	tmp = env->next;
	env->next = new;
	new->next = tmp;
	return (0);
}

char	*strchr_ret(const char *str, char c)
{
	size_t	len;
	size_t	i;
	char	*ret;

	len = 0;
	i = 0;
	if (!str || !c)
		return (NULL);
	while (str[len] != '\0' && str[len] != '=')
		len++;
	if (len == ft_strlen(str))
		return (NULL);
	ret = malloc(sizeof(char) * (len + 1));
	if (ret == NULL)
		return (NULL);
	while (i < len)
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);	
}

int	in_export(char **args, t_mini *mini, int arg_nb)
{
	t_env	*tmp;
	t_env	*tmp_2;
	char	*cmp;
	int		i;

	tmp = mini->export;
	i = 0;
	if (!tmp || tmp->value == NULL)
		return (1);
	cmp = strchr_ret(args[arg_nb], '=');
	if (cmp == NULL)
		return (1);
	if (!ft_strncmp(cmp, tmp->value, ft_strlen(cmp)))
	{
		if (tmp->next)
			mini->export = tmp->next;
		free_export(mini, tmp);
		return (0);
	}
	while (tmp)
	{
		if (!strncmp(cmp, tmp->next->value, ft_strlen(cmp)))
		{
			if (tmp->next->next == NULL)
				return (last_export(mini, tmp));
			tmp_2 = tmp->next->next;
			free_export(mini, tmp->next);
			tmp->next = tmp_2;
			free(cmp);
			return (1);
		}
		tmp = tmp->next;
	}
	free(cmp);
	return (0);
}

int	in_env(char *args, t_env *env)
{
	char	var_name[BUF_SIZE];
	char	env_name[BUF_SIZE];

	name_env(var_name, args);
	while (env && env->next)
	{
		name_env(env_name, env->value);
		if (ft_strcmp(var_name, env_name) == 0)
		{
			if (is_valid_env(args) != 1)
				return (1);
			ft_memdel(env->value);
			env->value = ft_strdup(args);
			return (1);
		}
		env = env->next;
	}
	return (0);
}

static int	show_error(int error, char *args)
{
	int	i;

	if (error == -1)
		ft_putstr_fd("export: not valid in this context: ", STDERR);
	if (error == 0 || error == -3)
		ft_putstr_fd("export: not a valid identifier: ", STDERR);
	i = 0;
	while (args[i] && (args[i] != '=' || error == -3))
	{
		ft_putchar_fd(args[i], STDERR);
		i++;
	}
	ft_putchar_fd('\n', STDERR);
	return (1);
}

char	*name_env(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] && src[i] != '=' && ft_strlen(src) < BUF_SIZE 
			&& src[i] != ' ')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	mini_export(char **args, t_mini *mini, t_env *env, t_env *export)
{
	int		new_env;
	int		error;
	char	*arg;
	int		arg_nb;

	arg_nb = 1;
	if (exa(args, env, export))
		return (0);
	while (args[arg_nb])
	{
		error = is_valid_env(args[arg_nb]);
		if (args[arg_nb][0] == '=')
			error = -3;
		if (error <= 0)
			return (show_error(error, args[arg_nb]));
		in_export(args, mini, arg_nb);
		arg = ex_arg(args, arg, arg_nb);
		new_env = in_env(arg, env);
		if (error == 1 && new_env == 0)
			env_add(arg, env);
		if (error == 2 && new_env == 0 && check_double(arg, export) == 0)
			export_add(arg, export);
		arg_nb++;
	}
	return (0);
}
