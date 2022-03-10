/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_baselen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamon <thamon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 14:55:53 by thamon            #+#    #+#             */
/*   Updated: 2022/03/04 20:25:20 by thamon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_baselen(int nb, int base)
{
	int	size;

	size = 0;
	if (base < 2)
		return (0);
	if (nb == 0)
		return (1);
	if (nb < 0)
		size++;
	while (nb != 0)
	{
		nb = nb / base;
		size++;
	}
	return (size);
}
