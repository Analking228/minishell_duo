/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 16:29:57 by cjani             #+#    #+#             */
/*   Updated: 2021/01/06 17:56:15 by cquiana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			ft_env_srch_len(char *str)
{
	int		count;

	count = 0;
	while (*str)
	{
		if (*str == '=')
			return (count);
		count++;
		str++;
	}
	return (count);
}

int			minishell_export_str_prove(char *str1, char *str2)
{
	int		i;

	if (str1)
	{
		i = 0;
		while (((str1[i] == str2[i])) && (str1[i] && str2[i]))
		{
			if ((str1[i + 1] == '=') || (str2[i + 1] == '='))
			{
				return (1);
				ft_putendl_fd(str1, 1);
				ft_putendl_fd(str2, 1);
			}
			i++;
		}
	}
	return (0);
}
