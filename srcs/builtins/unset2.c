/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusaint- <jusaint-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 11:38:35 by jusaint-          #+#    #+#             */
/*   Updated: 2022/03/16 19:43:57 by jusaint-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_export(t_mini *mini, t_env *export)
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

int	last_export(t_mini *mini, t_env *export)
{
	free_export(mini, export->next);
	export->next = NULL;
	return (0);
}

int	unset_export(char **args, t_mini *mini, int arg)
{
	t_env	*tmp;
	t_env	*export;

	export = mini->export;
	if (!(args[arg]) || export->value == NULL)
		return (1);
	if (!ft_strncmp(args[arg], export->value, ft_strlen(args[arg])))
	{
		if (export->next)
			mini->export = export->next;
		free_export(mini, export);
	}
	while (export && export->next && export->value != NULL)
	{
		if (!ft_strncmp(args[arg], export->next->value, ft_strlen(args[arg])))
		{
			if (export->next->next == NULL)
				return (last_export(mini, export));
			tmp = export->next->next;
			free_export(mini, export->next);
			export->next = tmp;
		}
		export = export->next;
	}
	return (0);
}
