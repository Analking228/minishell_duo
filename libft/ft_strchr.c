/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarry <skarry@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 10:58:47 by skarry            #+#    #+#             */
/*   Updated: 2020/05/13 11:53:28 by skarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*fin;

	fin = (char *)s;
	while (*fin != c)
	{
		if (!*fin)
			return (NULL);
		fin++;
	}
	return (fin);
}
