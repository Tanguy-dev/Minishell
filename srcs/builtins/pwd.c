/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamon <thamon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 16:15:35 by thamon            #+#    #+#             */
/*   Updated: 2022/02/02 18:22:37 by thamon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_pwd(t_env *env)
{
	char	pwd[PATH_MAX];

	(void) env;
	if (getcwd(pwd, PATH_MAX))
	{
		ft_putendl_fd(pwd, STDOUT);
		return (0);
	}
	return (1);
}
