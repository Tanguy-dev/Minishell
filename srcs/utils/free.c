/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamon <thamon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 17:16:24 by thamon            #+#    #+#             */
/*   Updated: 2022/03/16 12:42:57 by jusaint-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_env *env)
{
	t_env	*temp;

	while (env && env->next)
	{
		temp = env;
		env = env->next;
		ft_memdel(temp->value);
		ft_memdel(temp);
	}
	ft_memdel(env->value);
	ft_memdel(env);
	clear_history();
}

void	free_all_export(t_env *export)
{
	t_env	*tmp;

	while (export->next)
	{
		tmp = export;
		export = export->next;
		ft_memdel(tmp->value);
		ft_memdel(tmp);
	}
	ft_memdel(export->value);
	ft_memdel(export);
}

void	free_array(char **array)
{
	int		i;

	i = 0;
	while (array[i])
	{
		if (array[i])
			ft_memdel(array[i]);
		i++;
	}
	if (array)
		ft_memdel(array);
}

void	free_token(t_token *token)
{
	while (token && token->next)
	{
		ft_memdel(token->str);
		token = token->next;
		ft_memdel(token->prev);
	}
	if (token)
	{
		ft_memdel(token->str);
		ft_memdel(token);
	}
}
