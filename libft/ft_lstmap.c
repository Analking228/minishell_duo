/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarry <skarry@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 23:15:06 by skarry            #+#    #+#             */
/*   Updated: 2020/05/17 12:28:10 by skarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *new_head;
	t_list *tmp;
	t_list *cur;

	if (lst == NULL || (new_head = ft_lstnew(f(lst->content))) == NULL)
		return (NULL);
	cur = new_head;
	tmp = lst->next;
	while (tmp)
	{
		if ((cur->next = ft_lstnew(f(tmp->content))) == NULL)
		{
			ft_lstclear(&new_head, del);
			return (NULL);
		}
		cur = cur->next;
		tmp = tmp->next;
	}
	return (new_head);
}
