/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamon <thamon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 12:44:09 by thamon            #+#    #+#             */
/*   Updated: 2022/03/16 13:15:29 by thamon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*malloc_lim(char *line)
{
	char	*new;
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (line[i])
	{
		if (is_sep(i, line))
			count++;
		i++;
	}
	new = malloc(sizeof(char) * (i + 2 * count + 1));
	return (new);
}

char	*line2(char *line, char *test, int i, int j)
{
	test = malloc(sizeof(char) + (ft_strlen(line) - 1));
	while (line[i])
		test[j++] = line[i++];
	test[j++] = '=';
	test[j] = '\0';
	return (test);
}

char	*find_limeeeeeee(char *new, int *j, int *i, char *line)
{
	if (new[*j - 1] != ' ')
		new[(*j)++] = ' ';
	new[(*j)++] = line[(*i)++];
	if (quote(line, *i) == 0 && line[*i] == '>')
		new[(*j)++] = line[(*i)++];
	if (line[*i] != ' ')
		new[(*j)++] = ' ';
	return (new);
}

char	*find_lim(char *line, t_mini *mini, t_env *env)
{
	char	*new;
	int		i;
	int		j;

	new = malloc_lim(line);
	i = 0;
	j = 0;
	mini->echo = 0;
	while (new && line[i])
	{
		if (quote(line, i) != 1 && line[i] == '$' && i && line[i - 1] != '\\'
			&& quote_check(line, i))
			new[j++] = dollar(line, i++, mini);
		else if (quote(line, i) == 0 && is_sep(i, line))
			new = find_limeeeeeee(new, &j, &i, line);
		else if (line[i] == '$' && line[i - 1] != '\\')
		{
			new[j++] = find_lim2(env, line, mini, i++);
		}
		else
			new[j++] = line[i++];
	}
	return (lim_test(new, j, line));
}

int	is_valid_arg(t_token *token)
{
	t_token	*prev;

	if (!token || is_type(token, CMD) || is_type(token, ARG))
	{
		prev = prev_sep(token, 0);
		if (!prev || is_type(token, END) || is_type(token, PIPE))
			return (1);
		return (0);
	}
	else
		return (0);
}
