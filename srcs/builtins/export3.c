/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusaint- <jusaint-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 11:32:39 by jusaint-          #+#    #+#             */
/*   Updated: 2022/03/17 19:01:24 by jusaint-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_add(char *value, t_env *export)
{
	t_env	*new_export;
	t_env	*tmp;

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

int	check_double(char *arg, t_env *export)
{
	t_env	*tmp;
	char	*cmp;

	if (export == NULL || export->value == NULL || arg == NULL)
		return (0);
	tmp = export;
	cmp = ft_strdup(arg);
	while (tmp)
	{
		if (!strncmp(cmp, tmp->value, ft_strlen(tmp->value)))
		{
			free(cmp);
			return (1);
		}
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	free(cmp);
	return (0);
}

int	export_search_destroy(char *cmp, t_mini *mini, t_env *tmp, t_env *tmp_2)
{
	if (!ft_strncmp(cmp, tmp->value, ft_strlen(cmp)))
	{
		if (tmp->next)
			mini->export = tmp->next;
		free_export(mini, tmp);
		return (0);
	}
	while (tmp && tmp->next)
	{
		if (ft_strlen(cmp) != ft_strlen(tmp->value))
			return (1);
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

int	in_export(char **args, t_mini *mini, int arg_nb)
{
	t_env	*tmp;
	t_env	*tmp_2;
	char	*cmp;

	tmp = mini->export;
	tmp_2 = NULL;
	if (!tmp || tmp->value == NULL)
		return (1);
	cmp = strchr_ret(args[arg_nb], '=');
	if (cmp == NULL)
		return (1);
	if (ft_strlen(cmp) != ft_strlen(tmp->value))
		return (1);
	export_search_destroy(cmp, mini, tmp, tmp_2);
	return (0);
}
