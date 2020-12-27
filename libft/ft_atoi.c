/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarry <skarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 11:06:02 by skarry            #+#    #+#             */
/*   Updated: 2020/10/13 11:56:38 by skarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	long long int		i;
	long long int		res;

	i = 1;
	res = 0;
	while ((*str == ' ') || (*str == '\t') || (*str == '\n')
		|| (*str == '\v') || (*str == '\f') || (*str == '\r'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			i = -1;
		str++;
	}
	while (ft_isdigit((int)*str) && res < 2147483648)
	{
		res = res * 10 + (long long int)(*str - '0');
		str++;
	}
	if (res > 2147483648 && i == -1)
		res = 2147483648;
	if (res > 2147483647 && i == 1)
		res = 2147483647;
	return ((int)(res * i));
}
