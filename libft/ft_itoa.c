/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarry <skarry@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 09:46:31 by skarry            #+#    #+#             */
/*   Updated: 2020/05/15 23:26:43 by skarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*str_constructor(int len, int ren, int negativ)
{
	char	*str;

	if (!((str = (char*)malloc(sizeof(char) * (len + 1)))))
		return (NULL);
	str[len--] = '\0';
	while (ren != 0)
	{
		str[len--] = ren % 10 + '0';
		ren /= 10;
	}
	if (negativ == -1)
		str[len] = '-';
	return (str);
}

char		*ft_itoa(int n)
{
	int		negativ;
	int		ren;
	int		len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	len = 0;
	negativ = 0;
	if (n < 0)
	{
		negativ = -1;
		n *= -1;
		len++;
	}
	ren = n;
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	return (str_constructor(len, ren, negativ));
}
