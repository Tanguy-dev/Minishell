/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamon <thamon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 16:31:24 by thamon            #+#    #+#             */
/*   Updated: 2020/11/19 16:47:56 by thamon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*supp;

	if (!del)
		return ;
	while (*lst)
	{
		del((*lst)->content);
		supp = *lst;
		*lst = supp->next;
		free(supp);
	}
	*lst = NULL;
}
