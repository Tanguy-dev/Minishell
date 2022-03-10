/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamon <thamon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 15:25:34 by thamon            #+#    #+#             */
/*   Updated: 2022/03/04 20:21:37 by thamon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nblen(unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (n >= 10)
	{
		n /= 10;
		i++;
	}
	return (i + 1);
}

char	*ft_itoa(int n)
{
	char			*str;
	unsigned int	len;
	unsigned int	nb;
	unsigned int	i;

	nb = n;
	if (n < 0)
		nb = -n;
	len = ft_nblen(nb);
	i = 0;
	str = (char *)malloc(sizeof(char *) * len + 2);
	if (n < 0)
	{
		str[i] = '-';
		len++;
	}
	i = len - 1;
	while (nb >= 10)
	{
		str[i--] = nb % 10 + 48;
		nb /= 10;
	}
	str[i] = nb % 10 + 48;
	str[len] = '\0';
	return (str);
}
