/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamon <thamon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 16:51:49 by thamon            #+#    #+#             */
/*   Updated: 2022/03/14 18:02:36 by jusaint-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parse2(t_mini *mini, t_token *token, int number)
{
	if (number == 0)
	{
		if (mini->ret)
			ft_putstr_fd("👎 ", STDERR);
		else
			ft_putstr_fd("👍 ", STDERR);
		ft_putstr_fd("\033[0;32m\033[1mMinishell : \033[0m", STDERR);
	}
	else if (number == 1)
	{
		ft_putstr_fd("bash: syntax error near unexpected token `", STDERR);
		if (token->next)
			ft_putstr_fd(token->next->str, STDERR);
		if (!token->next)
			ft_putstr_fd("newline", STDERR);
		ft_putendl_fd("\'", STDERR);
	}
}

int	check_line(t_mini *mini, t_token *token)
{
	while (token)
	{
		if (what_type(token, "CDO") && (!token->next
				|| what_type(token->next, "CDOEP")))
		{
			parse2(mini, token, 1);
			mini->ret = 258;
			return (0);
		}
		if (what_type(token, "PE") && (!token->next
				|| !token->prev || what_type(token->next, "CODEP")))
		{
			ft_putstr_fd("bash: syntax error near unexpected token `", STDERR);
			ft_putstr_fd(token->str, STDERR);
			ft_putendl_fd("\'", STDERR);
			mini->ret = 258;
			return (0);
		}
		token = token->next;
	}
	return (1);
}

char	*test1(t_mini *mini)
{
	if (mini->ret && mini->ret != 126)
		return (ERROR_PROMPT);
	return (PROMPT);
}

static void	parse3(t_mini *mini, char *line, t_token *token)
{
	add_history(line);
	ft_memdel(line);
	multiple_arg(mini);
	while (token)
	{
		if (is_type(token, ARG))
			token_type(token, 0);
		token = token->next;
	}
}

void	parse(t_mini *mini)
{
	char		*line;
	t_token		*token;

	signal(SIGINT, &sig_int);
	signal(SIGQUIT, &sig_quit);
	line = readline(test1(mini));
	if (!line)
	{
		ft_memdel(line);
		ft_putendl_fd("exit", STDERR);
		exit(0);
	}
	if (g_sig.sigint == 1)
		mini->ret = g_sig.exit_status;
	if (check_quote(mini, line))
		return ;
	line = find_lim(line, mini, mini->env);
	mini->token = get_token(line);
	if (mini->check == 1)
	{
		mini->check = 0;
		line = check_env(line);
	}
	token = mini->token;
	parse3(mini, line, token);
}
