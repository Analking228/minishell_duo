/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarry <skarry@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 13:56:23 by skarry            #+#    #+#             */
/*   Updated: 2020/05/21 21:25:35 by skarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t n)
{
	size_t	j;

	if (ft_strlen(dst) >= n)
		return (ft_strlen(src) + n);
	j = 0;
	while (dst[j] && j < (n - 1))
		j++;
	while (*src && j < (n - 1))
	{
		dst[j] = *src;
		j++;
		src++;
	}
	dst[j] = '\0';
	return (ft_strlen(src) + ft_strlen(dst));
}
