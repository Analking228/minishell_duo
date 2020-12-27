/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarry <skarry@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 21:13:34 by skarry            #+#    #+#             */
/*   Updated: 2020/05/17 18:52:03 by skarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*fin;

	fin = (char *)s + ft_strlen(s);
	while (*fin != c)
	{
		if (ft_strncmp(fin, s, ft_strlen(s)) == 0)
			return (NULL);
		fin--;
	}
	return (fin);
}
