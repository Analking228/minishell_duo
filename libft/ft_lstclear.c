/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarry <skarry@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 15:08:23 by skarry            #+#    #+#             */
/*   Updated: 2020/05/14 17:58:44 by skarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*pip;

	if (*lst)
	{
		while (*lst)
		{
			pip = (*lst)->next;
			ft_lstdelone(*lst, del);
			(*lst) = pip;
		}
	}
}
