/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarry <skarry@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 13:56:35 by skarry            #+#    #+#             */
/*   Updated: 2020/05/20 14:04:29 by skarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t n)
{
	int		i;
	size_t	res;

	if (!src || !dest)
		return (0);
	res = 0;
	while (src[res] != '\0')
		res++;
	i = 0;
	while (src[i] != '\0' && i < ((int)n - 1))
	{
		dest[i] = src[i];
		i++;
	}
	if (n)
		dest[i] = '\0';
	return (res);
}
