/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusaint- <jusaint-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 11:32:39 by jusaint-          #+#    #+#             */
/*   Updated: 2022/03/16 12:34:33 by jusaint-         ###   ########.fr       */
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
