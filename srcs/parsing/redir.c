/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamon <thamon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 23:28:58 by thamon            #+#    #+#             */
/*   Updated: 2022/03/15 19:50:50 by thamon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*echo_test(char *line, int k, int j, char *test)
{
	while (line[k])
	{
		if (line[k] == '$')
		{
			if (line[k + 1] != '$')
			{
				if (quote_check(line, k) == 0)
					return (test);
				else
				{
					k++;
					while (line[k] != ' ' && ft_isalnum(line[k]))
						test[j++] = line[k++];
					test[j++] = '=';
					test[j] = '\0';
					return (test);
				}
			}
		}
		k++;
	}
	return (test);
}

void	redir(t_mini *mini, t_token *token, int type)
{
	ft_close(mini->fdout);
	if (type == CHEVRON)
		mini->fdout = open(token->str, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	else
		mini->fdout = open(token->str, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	if (mini->fdout == -1)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(token->str, STDERR);
		ft_putendl_fd(": No such file or directory", STDERR);
		mini->ret = 1;
		mini->no_run = 1;
		return ;
	}
	dup2(mini->fdout, STDOUT);
}

void	open_chev(t_mini *mini, t_token *token)
{
	ft_close(mini->fdin);
	mini->fdin = open(token->str, O_RDONLY, S_IRWXU);
	if (mini->fdin == -1)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(token->str, STDERR);
		ft_putendl_fd(": No such file or directory", STDERR);
		mini->ret = 1;
		mini->no_run = 1;
		return ;
	}
	dup2(mini->fdin, STDIN);
}

int	pipee(t_mini *mini)
{
	pid_t	pid;
	int		pipefd[2];

	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		ft_close(pipefd[1]);
		dup2(pipefd[0], STDIN);
		mini->pipin = pipefd[0];
		mini->pid = -1;
		mini->parent = 0;
		mini->no_run = 0;
		return (2);
	}
	else
	{
		ft_close(pipefd[0]);
		dup2(pipefd[1], STDOUT);
		mini->pipout = pipefd[1];
		mini->pid = pid;
		mini->end = 0;
		return (1);
	}
}
