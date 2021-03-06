/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamon <thamon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 22:52:07 by thamon            #+#    #+#             */
/*   Updated: 2022/03/19 19:10:24 by thamon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_env(char *env)
{
	int	i;

	i = 0;
	if (ft_isdigit(env[i]) == 1 || ft_isalnum(env[i]) == 0)
		return (0);
	while (env[i] && env[i] != '=')
	{
		if (ft_isalnum(env[i]) == 0 && env[i] != '\"')
			return (0);
		i++;
	}
	if (env[i] != '=')
		return (2);
	else
		return (1);
}

int	env_value_len(const char *env)
{
	int		i;
	int		size_name;

	size_name = 0;
	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	i++;
	while (env[i++])
		size_name++;
	return (size_name);
}

char	*env_value(char *env)
{
	int		i;
	int		j;
	int		size_alloc;
	char	*env_value;

	size_alloc = env_value_len(env) + 1;
	env_value = malloc(sizeof(char) * size_alloc);
	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	i += 1;
	j = 0;
	while (env[i])
		env_value[j++] = env[i++];
	env_value[j] = '\0';
	return (env_value);
}

char	*get_env_value(char *arg, t_env *env)
{
	char	env_name[BUF_SIZE];
	char	*env_val;

	env_val = ft_strdup("");
	while (env && env->value)
	{
		name_env(env_name, env->value);
		if (ft_strcmp(arg, env_name) == 0)
		{
			ft_memdel(env_val);
			env_val = env_value(env->value);
			return (env_val);
		}
		env = env->next;
	}
	return (env_val);
}

int	env_char(int c)
{
	if (ft_isalnum(c) == 1 || c == '_')
		return (1);
	return (0);
}
