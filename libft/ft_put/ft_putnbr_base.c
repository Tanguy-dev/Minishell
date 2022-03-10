/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamon <thamon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 15:18:06 by thamon            #+#    #+#             */
/*   Updated: 2022/03/04 20:26:54 by thamon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	error(char *base)
{
	int	i;
	int	j;

	if (!base)
		return (0);
	i = 0;
	while (base[i])
	{
		j = i + 1;
		if (base[i] == '+' || base[i] == '-')
			return (0);
		if (base[i] < 32 || base[i] > 126)
			return (0);
		while (base[j])
		{
			if (base[i] == base[j])
				return (0);
			j++;
		}
		i++;
	}
	if (i < 2)
		return (0);
	return (i);
}

static void	display(int nbr, char *base, unsigned int base_size)
{
	unsigned int	nb;

	if (nbr < 0)
	{
		nb = nbr * -1;
		ft_putchar('-');
	}
	else
		nb = nbr;
	if (nb >= base_size)
		display(nb / base_size, base, base_size);
	ft_putchar(base[nb % base_size]);
}

void	ft_putnbr_base(int nbr, char *base)
{
	unsigned int	base_size;

	base_size = 2;
	base_size = error(base);
	if (!base_size)
		return ;
	display(nbr, base, base_size);
}
