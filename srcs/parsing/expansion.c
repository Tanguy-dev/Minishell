/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamon <thamon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 13:50:51 by thamon            #+#    #+#             */
/*   Updated: 2022/02/27 15:27:27 by thamon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	arg_size(char *arg, t_env *env, int ret)
{
	int	i;
	int	size;

	i = -1;
	size = 0;
	while (arg[++i])
	{
		if (arg[i] == EXPANSION)
		{
			i++;
			if ((arg[i] == '\0' || ft_isalnum(arg[i]) == 0) && arg[i] != '?')
				size++;
			else
				size += get_arg_len(i, arg, env, ret);
			if (ft_isdigit(arg[i]) == 0)
				while (arg[i + 1] && env_char(arg[i]))
					i++;
			else
				size--;
		}
		size++;
	}
	return (size);
}

static char	*get_value(const char *arg, int pos, t_env *env, int ret)
{
	char	var_name[BUF_SIZE];
	char	*var_value;
	int		i;

	i = 0;
	if (arg[pos] == '?')
	{
		var_value = ft_itoa(ret);
		return (var_value);
	}
	if (ft_isdigit(arg[pos]))
		return (NULL);
	while (arg[pos] && env_char(arg[pos]) == 1 && i < BUF_SIZE)
	{
		var_name[i] = arg[pos];
		pos++;
		i++;
	}
	var_name[i] = '\0';
	var_value = get_env_value(var_name, env);
	return (var_value);
}

static int	vallcpy(char *new_arg, const char *env_value, int pos)
{
	int		i;

	i = 0;
	while (env_value[i])
		new_arg[pos++] = env_value[i++];
	return (i);
}

static void	inser_var(t_expansion *ex, char *arg, t_env *env, int ret)
{
	char	*env_value;

	env_value = get_value(arg, ex->j, env, ret);
	if (env_value)
		ex->i += vallcpy(ex->str, env_value, ex->i);
	else
		ex->i += 0;
	ft_memdel(env_value);
	if (arg[ex->j == '?'])
		ex->j++;
	if (ft_isdigit(arg[ex->j]) == 0 && arg[ex->j - 1] != '?')
		while (env_char(arg[ex->j]) == 1)
			ex->j++;
	else
		if (arg[ex->j - 1] != '?')
			ex->j++;
}

char	*expansion(char *arg, t_env *env, int ret)
{
	t_expansion	ex;
	int			arg_len;

	arg_len = arg_size(arg, env, ret);
	ex.str = malloc(sizeof(char) * arg_len + 1);
	ex.i = 0;
	ex.j = 0;
	while (ex.i < arg_len && arg[ex.j])
	{
		while (arg[ex.j] == EXPANSION)
		{
			ex.j++;
			if ((arg[ex.j] == '\0' || ft_isalnum(arg[ex.j]) == 0)
				&& arg[ex.j] != '?')
				ex.str[ex.i++] = '$';
			else
				inser_var(&ex, arg, env, ret);
		}
		ex.str[ex.i++] = arg[ex.j++];
	}
	ex.str[ex.i] = '\0';
	return (ex.str);
}
