/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamon <thamon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 16:45:34 by thamon            #+#    #+#             */
/*   Updated: 2022/03/20 17:12:56 by thamon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtins(char *cmd)
{
	if (ft_strcmp("echo", cmd) == 0)
		return (1);
	else if (ft_strcmp("cd", cmd) == 0)
		return (1);
	else if (ft_strcmp("pwd", cmd) == 0)
		return (1);
	else if (ft_strcmp("export", cmd) == 0)
		return (1);
	else if (ft_strcmp("unset", cmd) == 0)
		return (1);
	else if (ft_strcmp("env", cmd) == 0)
		return (1);
	return (0);
}

int	exec_builtins(t_mini *mini, char **cmd, t_token *token)
{
	int	ret;

	ret = 0;
	if (ft_strcmp("echo", cmd[0]) == 0)
		ret = mini_echo(cmd);
	if (ft_strcmp("cd", cmd[0]) == 0)
		ret = mini_cd(cmd, mini->env);
	if (ft_strcmp("pwd", cmd[0]) == 0)
		ret = mini_pwd(mini->env);
	if (ft_strcmp("export", cmd[0]) == 0 && its_pipe(token) == 0)
	{
		mini_export(cmd, mini, mini->env, mini->export);
		ret = mini->ret;
	}
	if (ft_strcmp("unset", cmd[0]) == 0 && its_pipe(token) == 0)
		ret = mini_unset(cmd, mini);
	if (ft_strcmp("env", cmd[0]) == 0)
		ret = mini_env(mini->env);
	return (ret);
}
