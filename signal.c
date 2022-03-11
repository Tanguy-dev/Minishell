/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamon <thamon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 18:05:05 by thamon            #+#    #+#             */
/*   Updated: 2022/03/11 15:06:11 by jusaint-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../../../../.brew/opt/readline/include/readline/readline.h"

void	sig_quit(int a)
{
	char	*nbr;

	nbr = ft_itoa(a);
	if (g_sig.pid != 0)
	{
		ft_putstr_fd("Quit: ", STDERR);
		ft_putendl_fd(nbr, STDERR);
		g_sig.exit_status = 131;
		g_sig.sigquit = 1;
	}
	else
		ft_putstr_fd("\b\b  \b\b", STDERR);
	ft_memdel(nbr);
}

void	sig_int(int a)
{
	(void)a;
	if (g_sig.pid == 0)
	{
//		ft_putstr_fd("\b\b\n\033[0;32m\033[1m👎 Minishell : \033[0m", STDERR);
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_sig.exit_status = 1;
	}
	else
	{
		ft_putstr_fd("\n", STDERR);
		rl_on_new_line();
		g_sig.exit_status = 130;
	}
	g_sig.sigint = 1;
}
