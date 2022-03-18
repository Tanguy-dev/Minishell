/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamon <thamon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 18:39:12 by thamon            #+#    #+#             */
/*   Updated: 2022/03/18 12:27:29 by thamon           ###   ########.fr       */
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

int	mini_export2(char **args, t_mini *mini, int arg_nb, int error)
{
	char	*arg;
	int		new_env;

	arg = NULL;
	in_export(args, mini, arg_nb);
	arg = ex_arg(args, arg, arg_nb);
	new_env = in_env(arg, mini->env);
	if (error == 1 && new_env == 0)
		env_add(arg, mini->env);
	if (error == 2 && new_env == 0 && check_double(arg, mini->export) == 0)
		export_add(arg, mini->export);
	return (0);
}

int	mini_export(char **args, t_mini *mini, t_env *env, t_env *export)
{
	int		error;
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
			show_error(error, args[arg_nb]);
		else
			mini_export2(args, mini, arg_nb, error);
		arg_nb++;
	}
	return (0);
}
