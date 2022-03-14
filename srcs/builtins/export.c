/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamon <thamon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 18:39:12 by thamon            #+#    #+#             */
/*   Updated: 2022/03/14 18:11:47 by jusaint-         ###   ########.fr       */
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

/* new function to add var that won't be in the env list, in the export list */

int export_add(char *value, t_env *export)
{
	t_env *new_export;
	t_env *tmp;

	if (export->value == NULL)
		export->value = ft_strdup(value);
	else
	{
		new_export = malloc(sizeof(t_env));
		new_export->value = ft_strdup(value);
		while (export->next)
			export = export->next;
		tmp = export->next;
		export->next = new_export;
		new_export->next = tmp;
	}
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
	else if (error == 0 || error == -3)
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
	while (src[i] && src[i] != '=' && ft_strlen(src) < BUF_SIZE)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	mini_export(char **args, t_env *env, t_env *export)
{
	int		new_env;
	int		error;
	char	*arg;

	new_env = 0;
	arg = NULL;
	if (exa(args, env, export))
		return (0);
	else
	{
		error = is_valid_env(args[1]);
		if (args[1][0] == '=')
			error = -3;
		if (error <= 0)
			return (show_error(error, args[1]));
		arg = ex_arg(args, arg);
		if (error == 2)
			new_env = 1;
		else
			new_env = in_env(arg, env);
		if (new_env == 0 && error == 1)
			env_add(arg, env);
/* if var has no '=', add it to export only */
		if (new_env == 1 && error == 2)
			export_add(arg, export);
	}
	return (0);
}
