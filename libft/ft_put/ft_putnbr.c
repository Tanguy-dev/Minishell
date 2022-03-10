/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamon <thamon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 15:39:16 by thamon            #+#    #+#             */
/*   Updated: 2020/12/17 16:56:12 by thamon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_max(int n)
{
	if (n == -2147483648)
		ft_putstr("-2147483648");
	else
		ft_putchar('0');
}

void	ft_putnbr(int n)
{
	int		i;
	char	c[10];

	if (n == 0 || n == -2147483648)
	{
		ft_max(n);
		return ;
	}
	if (n < 0)
	{
		ft_putchar('-');
		n = -n;
	}
	i = 0;
	while (n > 0)
	{
		c[i] = n % 10 + '0';
		n = n / 10;
		i++;
	}
	i--;
	while (i >= 0)
		ft_putchar(c[i--]);
}
