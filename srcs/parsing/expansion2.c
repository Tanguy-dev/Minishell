/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamon <thamon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 13:50:51 by thamon            #+#    #+#             */
/*   Updated: 2022/03/12 18:52:22 by thamon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ret_size(int ret)
{
	char	*tmp;
	int		ret_len;

	tmp = ft_itoa(ret);
	ret_len = ft_strlen(tmp);
	ft_memdel(tmp);
	return (ret_len);
}

int	get_arg_len(int pos, char *arg, t_env *env, int ret)
{
	char	var_name[BUF_SIZE];
	char	*var_value;
	int		i;

	i = 0;
	if (arg[pos] == '?')
		return (ret_size(ret));
	if (ft_isdigit(arg[pos]))
		return (0);
	while (arg[pos] && env_char(arg[pos]) == 1 && i < BUF_SIZE)
	{
		var_name[i] = arg[pos];
		pos++;
		i++;
	}
	var_name[i] = '\0';
	var_value = get_env_value(var_name, env);
	i = ft_strlen(var_value);
	ft_memdel(var_value);
	return (i);
}

int	is_sep(int i, char *line)
{
	if (i > 0 && line[i - 1] == '\\' && ft_strchr("<>;|", line[i]))
		return (0);
	else if (ft_strchr("<>;|", line[i]) && quote(line, i) == 0)
		return (1);
	else
		return (0);
}
