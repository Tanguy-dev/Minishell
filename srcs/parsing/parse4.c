/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamon <thamon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 20:10:42 by thamon            #+#    #+#             */
/*   Updated: 2022/03/11 12:40:47 by thamon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_check(char *line, int i)
{
	int	j;
	int	k;

	j = 0;
	while (line[i] && j <= i)
	{
		if (line[j] == '\'' && k == 0)
			k = 1;
		else if (line[j] == '\'' && k == 1)
			k = 0;
		j++;
	}
	if (k == 1)
		return (0);
	return (1);
}

static char	*echo_env(char *line, char *test)
{
	int	k;
	int	j;

	k = 0;
	j = 0;
	test = malloc(sizeof(char) + (ft_strlen(line) - 1));
	while (line[k] != ' ')
		k++;
	while (line[k])
	{
		if (line[k] == '$' && quote_check(line, k))
		{
			if (line[k + 1] != '$')
			{
				k++;
				while (line[k] != ' ' && ft_isalnum(line[k]))
				{
					test[j++] = line[k++];
				}
				test[j++] = '=';
				test[j] = '\0';
				return (test);
			}
		}
		k++;
	}
	return (test);
}

char	find_lim2(t_env *env, char *line, t_mini *mini, int i)
{
	char	*test;

	test = NULL;
	if (ft_strncmp(line, "echo", 4) == 0)
	{
		test = echo_env(line, test);
	}
	else
		test = line2(line, test, 1, 0);
	while (env && env->value)
	{
		if (ft_strncmp(test, env->value, ft_strlen(test)) == 0)
		{
			mini->check = 1;
			ft_memdel(test);
			return ((char)(-line[i++]));
		}
		env = env->next;
	}
	ft_memdel(test);
	return (line[i++]);
}

char	*lim_test(char *new, int j, char *line)
{
	new[j] = '\0';
	ft_memdel(line);
	return (new);
}

char	dollar(char *line, int i, t_mini *mini)
{
	mini->check = 1;
	return ((char)(-line[i++]));
}
