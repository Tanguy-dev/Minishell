/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamon <thamon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 16:42:07 by thamon            #+#    #+#             */
/*   Updated: 2022/03/16 12:35:51 by jusaint-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	env_size(t_env *env)
{
	size_t	env_len;

	env_len = 0;
	while (env && env->next)
	{
		if (env->value)
		{
			env_len += ft_strlen(env->value);
			env_len++;
		}
		env = env->next;
	}
	return (env_len);
}

char	*env_on_str(t_env *env)
{
	char	*env1;
	int		i;
	int		j;

	i = 0;
	env1 = malloc(sizeof(char) * env_size(env) + 1);
	while (env && env->next)
	{
		if (env->value)
		{
			j = 0;
			while (env->value[j])
			{
				env1[i] = env->value[j];
				j++;
				i++;
			}	
		}
		if (env->next->next)
			env1[i++] = '\n';
		env = env->next;
	}
	env1[i] = '\0';
	return (env1);
}

int	set_env(t_mini *mini, char **env)
{
	t_env	*env1;
	t_env	*env2;
	int		i;

	env1 = malloc(sizeof(t_env));
	env1->value = ft_strdup(env[0]);
	env1->next = NULL;
	mini->env = env1;
	i = 1;
	while (env && env[i])
	{
		env2 = malloc(sizeof(t_env));
		env2->value = ft_strdup(env[i]);
		env2->next = NULL;
		env1->next = env2;
		env1 = env2;
		i++;
	}
	return (0);
}

t_env	*set_export(char *value)
{
	t_env	*new_export;

	new_export = malloc(sizeof(t_env));
	if (value == NULL)
		new_export->value = NULL;
	else
		new_export->value = ft_strdup(value);
	new_export->next = NULL;
	return (new_export);
}

char	*check_env(char *line)
{
	char	*replace;
	int		i;

	replace = malloc(sizeof(char) + (ft_strlen(line) + 1));
	i = 0;
	while (line[i])
	{
		if (!ft_isascii(line[i]))
			replace[i] = '$';
		else
			replace[i] = line[i];
		i++;
	}
	replace[i] = '\0';
	free(line);
	return (replace);
}
