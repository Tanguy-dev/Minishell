/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamon <thamon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 18:44:57 by thamon            #+#    #+#             */
/*   Updated: 2022/02/09 12:12:51 by thamon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*next_cmd(t_token *token, int i)
{
	if (token && i)
		token = token->next;
	while (token && token->type != CMD)
	{
		token = token->next;
		if (token && token->type == CMD && token->prev == NULL)
			;
		else if (token && token->type == CMD && token->prev->type != END)
			token = token->next;
	}
	return (token);
}

t_token	*next_sep(t_token *token, int skip)
{
	if (token && skip)
		token = token->next;
	while (token && token->type < PIPE)
		token = token->next;
	return (token);
}

t_token	*prev_sep(t_token *token, int skip)
{
	if (token && skip)
		token = token->prev;
	while (token && token->type < PIPE)
		token = token->prev;
	return (token);
}

static void	multiple_arg2(t_mini *mini, t_token *token, t_token *prev)
{
	if (prev)
		token->next = prev->next;
	else
		token->next = mini->token;
	if (!prev)
		prev = token;
	prev->next->prev = token;
	if (!mini->token->prev)
		prev->next = token;
	if (mini->token->prev)
		mini->token = mini->token->prev;
}

void	multiple_arg(t_mini *mini)
{
	t_token	*token;
	t_token	*prev;

	token = mini->token;
	while (token)
	{
		prev = prev_sep(token, 0);
		if (is_type(token, ARG) && what_type(prev, "COD"))
		{
			while (is_valid_arg(prev) == 0)
				prev = prev->prev;
			token->prev->next = token->next;
			if (token->next)
				token->next->prev = token->prev;
			token->prev = prev;
			multiple_arg2(mini, token, prev);
		}
		token = token->next;
	}
}
