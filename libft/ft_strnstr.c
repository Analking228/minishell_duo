/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarry <skarry@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 22:04:11 by skarry            #+#    #+#             */
/*   Updated: 2020/05/13 13:31:20 by skarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str1, const char *str2, size_t n)
{
	size_t	len;

	if (*str2 == '\0')
		return ((char *)str1);
	len = ft_strlen(str2);
	while (*str1 && n-- >= len)
	{
		if (*str1 == *str2 && ft_memcmp(str1, str2, len) == 0)
			return ((char *)str1);
		str1++;
	}
	return (0);
}
