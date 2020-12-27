/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarry <skarry@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 17:45:52 by skarry            #+#    #+#             */
/*   Updated: 2020/05/17 19:02:48 by skarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *des, const void *src, int c, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	d = (unsigned char *)des;
	s = (unsigned char *)src;
	i = 0;
	while (n > i)
	{
		d[i] = s[i];
		if (s[i] == (unsigned char)c)
			return ((void *)des + i + 1);
		i++;
	}
	return (NULL);
}
