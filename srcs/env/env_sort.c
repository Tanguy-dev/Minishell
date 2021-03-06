/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamon <thamon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 22:39:22 by thamon            #+#    #+#             */
/*   Updated: 2022/03/17 18:41:47 by jusaint-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_env(char **tabe, int env_len)
{
	int		ordered;
	int		i;
	char	*tmp;

	ordered = 0;
	while (tabe && ordered == 0)
	{
		ordered = 1;
		i = 0;
		while (i < env_len - 1)
		{
			if (ft_strcmp(tabe[i], tabe[i + 1]) > 0)
			{
				tmp = tabe[i];
				tabe[i] = tabe[i + 1];
				tabe[i + 1] = tmp;
				ordered = 0;
			}
			i++;
		}
		env_len--;
	}
}

void	show_env(t_env *env, t_env *export)
{
	int		i;
	char	**tabe;
	char	*str_env;
	t_env	*tmp_export;

	str_env = env_on_str(env);
	tabe = ft_split(str_env, '\n');
	ft_memdel(str_env);
	sort_env(tabe, ft_strarraylen(tabe));
	i = 0;
	while (tabe[i])
	{
		ft_putstr("declare -x ");
		ft_putendl(tabe[i]);
		i++;
	}
	tmp_export = export;
	while (tmp_export && tmp_export->value != NULL)
	{
		printf("declare -x ");
		printf("%s\n", tmp_export->value);
		tmp_export = tmp_export->next;
	}
	free_array(tabe);
}
