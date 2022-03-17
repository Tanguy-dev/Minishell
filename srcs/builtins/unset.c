/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamon <thamon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 18:39:25 by thamon            #+#    #+#             */
/*   Updated: 2022/03/16 13:20:55 by thamon           ###   ########.fr       */
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

int	unset_env(char **args, t_mini *mini, int arg)
{
	t_env	*env;
	t_env	*tmp;

	env = mini->env;
	if (!ft_strncmp(args[arg], env->value, env_s(env->value)))
	{
		if (env->next)
			mini->env = env->next;
		free_envv(mini, env);
		return (0);
	}
	while (env && env->next)
	{
		if (!ft_strncmp(args[arg], env->next->value, env_s(env->next->value)))
		{
			tmp = env->next->next;
			free_envv(mini, env->next);
			env->next = tmp;
			return (0);
		}
		env = env->next;
	}
	return (0);
}

int	mini_unset(char **args, t_mini *mini)
{
	int		arg_nb;

	arg_nb = 1;
	if (!(args[1]))
		return (0);
	while (args[arg_nb])
	{
		unset_env(args, mini, arg_nb);
		unset_export(args, mini, arg_nb);
		arg_nb++;
	}
	return (0);
}
