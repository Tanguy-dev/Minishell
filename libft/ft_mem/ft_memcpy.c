/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamon <thamon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 12:32:41 by thamon            #+#    #+#             */
/*   Updated: 2022/03/04 20:26:02 by thamon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*s1;

	s1 = (char *)dest;
	if (!dest && !src)
		return (0);
	while (n != 0)
	{
		*s1 = *(char *)src;
		s1++;
		src++;
		n--;
	}
	return (dest);
}
