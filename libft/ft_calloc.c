/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarry <skarry@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 15:57:22 by skarry            #+#    #+#             */
/*   Updated: 2020/05/07 20:22:21 by skarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n, size_t b)
{
	unsigned char	*s;

	if (!(s = (unsigned char*)malloc(n * b)))
		return (NULL);
	ft_memset(s, 0, n * b);
	return (s);
}
