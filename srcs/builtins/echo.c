/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamon <thamon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 18:38:53 by thamon            #+#    #+#             */
/*   Updated: 2022/03/10 12:17:26 by thamon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_echo(char *line)
{
	char	*echo;
	int		k;

	k = 0;
	echo = malloc(ft_atoi(line));
	while (line[k] != ' ' && line[k] != '\0')
	{
		echo[k] = line[k];
		k++;
	}
	if (!ft_strcmp(echo, "echo"))
	{
		free(echo);
		return (0);
	}
	free(echo);
	return (1);
}

int	remove_backk(char *line)
{
	int	simple;
	int	doublee;
	int	i;

	simple = 0;
	doublee = 0;
	i = 0;
	while (line[i])
	{
		if (doublee == 0 && line[i] == '\"' && line[i - 1] != '\\')
			doublee = 1;
		else if (doublee == 1 && line[i] == '\"' && line[i - 1] != '\\')
			doublee = 0;
		if (simple == 0 && line[i] == '\'' && line[i - 1] != '\\')
			simple = 1;
		else if (simple == 1 && line[i] == '\'' && line[i - 1] != '\\')
			simple = 0;
		if (simple == 0 && doublee == 0 && line[i] == '\\')
			line[i] = ' ';
		i++;
	}
	return (0);
}

char	*remove_back(char *line)
{
	int	simple;
	int	doublee;
	int	i;

	simple = 0;
	doublee = 0;
	i = 5;
	while (line[i])
	{
		if (doublee == 0 && line[i] == '\"' && line[i - 1] != '\\')
			doublee = 1;
		else if (doublee == 1 && line[i] == '\"' && line[i - 1] != '\\')
			doublee = 0;
		else if (simple == 0 && line[i] == '\'' && line[i - 1] != '\\')
			simple = 1;
		else if (simple == 1 && line[i] == '\'' && line[i - 1] != '\\')
			simple = 0;
		if (simple == 0 && doublee == 0 && line[i] == '\\')
			ft_putchar(' ');
		i++;
	}
	return (line);
}

int	mini_echo(char **args)
{
	int		i;
	int		n_flags;

	i = 1;
	n_flags = 0;
	if (ft_strarraylen(args) > 1)
	{
		while (args[i] && ft_strcmp("-n", args[i]) == 0)
		{
			n_flags = 1;
			i++;
		}
		while (args[i])
		{
			ft_putstr_fd(args[i], STDOUT);
			if (args[i + 1] && args[i][0] != '\0' && args[i + 1][0] != '$')
				ft_putchar_fd(' ', STDOUT);
			i++;
		}
	}
	if (n_flags == 0)
		ft_putchar_fd('\n', STDOUT);
	return (0);
}
