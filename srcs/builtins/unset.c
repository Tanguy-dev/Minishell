/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamon <thamon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 18:39:25 by thamon            #+#    #+#             */
/*   Updated: 2022/03/16 13:16:14 by thamon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	env_s(char *env)
{
	int	i;

	i = 0;
	while (env && env[i] != '=')
		i++;
	return (i);
}

static void	free_envv(t_mini *mini, t_env *env)
{
	if (mini->env == env && env->next == NULL)
	{
		ft_memdel(mini->env->value);
		mini->env->value = NULL;
		mini->env->next = NULL;
		return ;
	}
	ft_memdel(env->value);
	ft_memdel(env);
}

static void	free_export(t_mini *mini, t_env *export)
{
	if (mini->export == export && export->next == NULL)
	{
		ft_memdel(mini->export->value);
		mini->export->value = NULL;
		mini->export->next = NULL;
		return ;
	}
	ft_memdel(export->value);
	ft_memdel(export);
}

// this shit is too long
int	unset_export(char **args, t_mini *mini, int arg_nb)
{
	t_env	*tmp;
	t_env	*export;

	export = mini->export;
	if (!(args[arg_nb]))
		return (0);
	if (export->value == NULL)
		return (0);
	if (!ft_strncmp(args[arg_nb], export->value, ft_strlen(args[arg_nb])))
	{
		if (export->next)
			mini->export = export->next;
		free_export(mini, export);
		return (0);
	}
	while (export && export->next && export->value != NULL)
	{
		if (!ft_strncmp(args[arg_nb], export->next->value, ft_strlen(args[arg_nb])))
		{
			if (export->next->next == NULL)
			{
				free_export(mini, export->next);
				export->next = NULL;
				return (0);
			}
			tmp = export->next->next;
			free_export(mini, export->next);
			export->next = tmp;
		}
		if (export->next == NULL)
			break;
		else
			export = export->next;
	}
	return (0);
}

int	mini_unset(char **args, t_mini *mini)
{
	t_env	*env;
	t_env	*tmp;
	int		arg_nb;

	env = mini->env;
	arg_nb = 1;
	if (!(args[1]))
		return (0);
	while (args[arg_nb])
	{
		// make funcc for unset_env
		if (!ft_strncmp(args[arg_nb], env->value, env_s(env->value)))
		{
			if (env->next)
				mini->env = env->next;
			free_envv(mini, env);
			return (0);
		}
		while (env && env->next)
		{
			if (!ft_strncmp(args[arg_nb], env->next->value, env_s(env->next->value)))
			{
				tmp = env->next->next;
				free_envv(mini, env->next);
				env->next = tmp;
				return (0);
			}
			env = env->next;
		}
		unset_export(args, mini, arg_nb);
		arg_nb++;
	}
	return (0);
}
