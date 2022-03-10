/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamon <thamon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 13:22:20 by thamon            #+#    #+#             */
/*   Updated: 2022/02/18 22:47:34 by thamon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_type(t_token *token, int type)
{
	if (token && token->type == type)
		return (1);
	else
		return (0);
}

int	what_type(t_token *token, char *type)
{
	if (ft_strchr(type, ' ') && is_type(token, EMPTY))
		return (1);
	else if (ft_strchr(type, 'X') && is_type(token, CMD))
		return (1);
	else if (ft_strchr(type, 'A') && is_type(token, ARG))
		return (1);
	else if (ft_strchr(type, 'P') && is_type(token, PIPE))
		return (1);
	else if (ft_strchr(type, 'C') && is_type(token, CHEVRON))
		return (1);
	else if (ft_strchr(type, 'O') && is_type(token, OPEN_CHEVRON))
		return (1);
	else if (ft_strchr(type, 'D') && is_type(token, DOUBLE_CHEVRON))
		return (1);
	else if (ft_strchr(type, 'E') && is_type(token, END))
		return (1);
	return (0);
}

int	its_pipe(t_token *token)
{
	while (token && is_type(token, END) == 0)
	{
		if (is_type(token, PIPE))
			return (1);
		token = token->next;
	}
	return (0);
}
