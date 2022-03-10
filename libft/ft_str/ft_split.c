/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamon <thamon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 13:14:59 by thamon            #+#    #+#             */
/*   Updated: 2022/03/04 20:30:02 by thamon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbword(char const *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (*s == '\0')
		return (0);
	while (*s)
	{
		if (*s == c)
			i = 0;
		else if (i == 0)
		{
			i = 1;
			j++;
		}
		s++;
	}
	return (j);
}

static int	ft_nbchar(char const *s, char c, int i)
{
	int	lng;

	lng = 0;
	while (s[i] != c && s[i])
	{
		lng++;
		i++;
	}
	return (lng);
}

static char	**ft_freee(char const **str, int j)
{
	while (j > 0)
	{
		j--;
		free((void *)str[j]);
	}
	free(str);
	return (NULL);
}

static char	**ft_atrib(char const *s, char **str, char c, int a)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (s[i] && j < a)
	{
		k = 0;
		while (s[i] == c)
			i++;
		str[j] = (char *)malloc(sizeof(char) * ft_nbchar(s, c, i) + 1);
		if (str[j] == NULL)
			return (ft_freee((const char **)str, j));
		while (s[i] && s[i] != c)
			str[j][k++] = s[i++];
		str[j][k] = '\0';
		j++;
	}
	str[j] = 0;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		i;

	if (s == NULL)
		return (NULL);
	i = ft_nbword(s, c);
	str = (char **)malloc(sizeof(char *) * (i + 1));
	if (str == NULL)
		return (NULL);
	return (ft_atrib(s, str, c, i));
}
