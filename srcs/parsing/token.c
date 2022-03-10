/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamon <thamon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 12:46:00 by thamon            #+#    #+#             */
/*   Updated: 2022/03/10 12:00:23 by thamon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ignor_sep(char *line, int i)
{
	if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == '>')
		return (1);
	else if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == '|')
		return (1);
	else if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == ';')
		return (1);
	else if (line[i] && line[i] == '\\' && line[i + 1]
		&& line[i + 1] == '>' && line[i + 2] && line[i + 2] == '>')
		return (1);
	return (0);
}

int	token_mal(char *line, int *i)
{
	int		count;
	int		j;
	char	c;

	count = 0;
	j = 0;
	c = ' ';
	while (line[*i + j] && (line[*i + j] != ' ' || c != ' '))
	{
		if (c == ' ' && (line[*i + j] == '\'' || line[*i + j] == '\"'))
		{
			c = line[*i + j++];
		}
		else if (c != ' ' && line[*i + j] == c)
		{
			count += 2;
			c = ' ';
			j++;
		}
		else
			j++;
		if (line[*i + j - 1] == '\\')
			count--;
	}
	return (j - count + 1);
}

t_token	*next_token(char *line, int *i)
{
	t_token	*token;
	int		j;
	char	c;

	j = 0;
	c = ' ';
	token = malloc(sizeof(t_token));
	token->str = malloc(sizeof(char) * token_mal(line, i));
	while (line[*i] && (line[*i] != ' ' || c != ' '))
	{
		if (c == ' ' && (line[*i] == '\'' || line[*i] == '\"') && !tk(line, *i))
			c = line[(*i)++];
		else if (c != ' ' && line[*i] == c)
			c = token_test(c, i);
		else if (line[*i] == '\\' && remove_backk(line) && (*i)++)
		{
			line = remove_back(line);
			if (check_echo(line))
				token->str[j++] = line[(*i)++];
		}
		else
			token->str[j++] = line[(*i)++];
	}
	token->str[j] = '\0';
	return (token);
}

void	token_type(t_token *token, int sep)
{
	if (ft_strcmp(token->str, "") == 0)
		token->type = EMPTY;
	else if (ft_strcmp(token->str, ">") == 0 && sep == 0)
		token->type = CHEVRON;
	else if (ft_strcmp(token->str, ">>") == 0 && sep == 0)
		token->type = DOUBLE_CHEVRON;
	else if (ft_strcmp(token->str, "<") == 0 && sep == 0)
		token->type = OPEN_CHEVRON;
	else if (ft_strcmp(token->str, ";") == 0 && sep == 0)
		token->type = END;
	else if (ft_strcmp(token->str, "|") == 0 && sep == 0)
		token->type = PIPE;
	else if (token->prev == NULL || token->prev->type >= PIPE)
		token->type = CMD;
	else
		token->type = ARG;
}

t_token	*get_token(char *line)
{
	t_token	*next;
	t_token	*prev;
	int		i;
	int		sep;

	i = 0;
	prev = NULL;
	next = NULL;
	ft_skip_space(line, &i);
	while (line[i])
	{
		sep = ignor_sep(line, i);
		next = next_token(line, &i);
		next->prev = prev;
		if (prev)
			prev->next = next;
		prev = next;
		token_type(next, sep);
		ft_skip_space(line, &i);
	}
	if (next)
		next->next = NULL;
	while (next && next->prev)
		next = next->prev;
	return (next);
}
