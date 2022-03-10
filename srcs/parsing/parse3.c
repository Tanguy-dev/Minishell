/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamon <thamon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 16:05:29 by thamon            #+#    #+#             */
/*   Updated: 2022/03/09 16:30:42 by thamon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote(char *line, int nb)
{
	int	i;
	int	nbr;

	i = 0;
	nbr = 0;
	while (i != nb && line[i])
	{
		if (i > 0 && line[i - 1] == '\\')
			;
		else if (nbr == 0 && line[i] == '\'')
			nbr = 1;
		else if (nbr == 1 && line[i] == '\'')
			nbr = 0;
		else if (nbr == 0 && line[i] == '\"')
			nbr = 1;
		else if (nbr == 1 && line[i] == '\"')
			nbr = 0;
		i++;
	}
	return (nbr);
}

int	quote2(char *line, int nb, int i)
{
	int	nbr;
	int	nbr2;

	i = 0;
	nbr = 0;
	nbr2 = 0;
	while (i != nb && line[i])
	{
		if (nbr == 0 && line[i] == '\'' && nbr2 == 0)
			nbr = 1;
		else if (line[i] == '\'' && line[i - 1] == '\\' && nbr == 1)
			;
		else if (nbr == 1 && line[i] == '\'')
			nbr = 0;
		else if (nbr2 == 0 && line[i] == '\"' && nbr == 0)
			nbr2 = 1;
		else if (line[i] == '\"' && line[i - 1] == '\\' && nbr2 == 1)
			;
		else if (nbr2 == 1 && line[i] == '\"')
			nbr2 = 0;
		i++;
	}
	if (nbr2 == 1 || nbr == 1)
		return (33);
	return (0);
}

int	check_quote(t_mini *mini, char *line)
{
	if (!check_echo(line) && quote2(line, ft_strlen(line) + 2, 0))
	{
		ft_putendl_fd("minishell: syntax error open quotes", STDERR);
		ft_memdel(line);
		mini->ret = 2;
		mini->token = NULL;
		return (1);
	}	
	if (quote(line, 2147483647))
	{
		if (!check_echo(line) && quote2(line, ft_strlen(line) + 2, 0))
			return (0);
		ft_putendl_fd("minishell: syntax error open quotes", STDERR);
		ft_memdel(line);
		mini->ret = 2;
		mini->token = NULL;
		return (1);
	}
	return (0);
}

int	tk(char *line, int i)
{
	if (line[i - 1] == '\\' && (line[i] == '\'' || line[i] == '\"'))
		return (1);
	else if (ft_strncmp(line, "export", 6) == 0)
		return (1);
	return (0);
}

char	token_test(char c, int *i)
{
	c = ' ';
	(*i)++;
	return (c);
}
