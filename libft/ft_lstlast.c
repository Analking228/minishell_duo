/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarry <skarry@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 14:19:18 by skarry            #+#    #+#             */
/*   Updated: 2020/05/14 17:58:55 by skarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstlast(t_list *lst)
{
	t_list		*first;
	t_list		*second;

	if (!lst)
		return (NULL);
	first = lst;
	while (first)
	{
		second = first;
		first = first->next;
	}
	return (second);
}
