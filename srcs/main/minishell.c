/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamon <thamon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 12:46:05 by thamon            #+#    #+#             */
/*   Updated: 2022/03/14 16:03:17 by jusaint-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sig	g_sig;

void	redir_exec(t_mini *mini, t_token *token)
{
	t_token	*prev;
	t_token	*next;
	int		pipe;

	next = next_sep(token, 0);
	prev = prev_sep(token, 0);
	pipe = 0;
	if (is_type(prev, CHEVRON))
		redir(mini, token, CHEVRON);
	else if (is_type(prev, DOUBLE_CHEVRON))
		redir(mini, token, DOUBLE_CHEVRON);
	else if (is_type(prev, PIPE))
		pipe = pipee(mini);
	else if (is_type(prev, OPEN_CHEVRON))
		open_chev(mini, token);
	if (next && is_type(next, END) == 0 && pipe != 1)
		redir_exec(mini, next->next);
	if ((is_type(prev, END) || is_type(prev, PIPE) || !prev)
		&& pipe != 1 && mini->no_run == 0)
		exec_cmd(mini, token);
}

void	test(t_mini *mini)
{
	if (mini->parent == 0)
	{
		free_token(mini->token);
		exit(mini->ret);
	}
	mini->no_run = 0;
}

void	start(t_mini *mini)
{
	t_token	*token;
	int		states;

	token = next_cmd(mini->token, 0);
	if (what_type(mini->token, "COD"))
		token = mini->token->next;
	while (mini->exit == 0 && token)
	{
		mini->parent = 1;
		mini->charge = 1;
		mini->end = 1;
		redir_exec(mini, token);
		close_fd(mini);
		reset_fd(mini);
		reset_std(mini);
		waitpid(-1, &states, 0);
		states = WEXITSTATUS(states);
		if (mini->end == 0)
			mini->ret = states;
		test(mini);
		token = next_cmd(token, 1);
	}
}

int	main(int ac, char **av, char **env)
{
	t_mini		mini;

	(void)ac;
	(void)av;
	ft_bzero(&mini, sizeof(t_mini));
	mini.in = dup(STDIN);
	mini.out = dup(STDOUT);
	reset_fd(&mini);
	set_env(&mini, env);
	mini.export = malloc(sizeof(t_env*));
	mini.export = NULL;
	while (mini.exit == 0)
	{
		ft_bzero(&g_sig, sizeof(t_sig));
		parse(&mini);
		if (mini.token && check_line(&mini, mini.token))
			start(&mini);
	}
	free_env(mini.env);
//	free_export	
	return (mini.ret);
}
