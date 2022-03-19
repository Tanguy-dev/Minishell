/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamon <thamon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 16:15:21 by thamon            #+#    #+#             */
/*   Updated: 2022/03/19 19:00:36 by thamon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_exit(t_mini *mini, char **cmd)
{
	mini->exit = 1;
	ft_putendl_fd("exit", STDERR);
	if (cmd[1] && ft_strisnum(cmd[1]) == 0)
	{
		mini->ret = 255;
		ft_putstr_fd("minishell: exit: ", STDERR);
		ft_putstr_fd(cmd[1], STDERR);
		ft_putendl_fd(": numeric argument required", STDERR);
	}
	else if (cmd[1] && cmd[2])
	{
		mini->ret = 1;
		mini->exit = 0;
		ft_putendl_fd("minishell: exit: too many arguments", STDERR);
	}
	else if (cmd[1])
		mini->ret = ft_atoi(cmd[1]);
	return (mini->ret);
}
