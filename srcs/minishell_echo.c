/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_echo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 16:29:57 by cjani             #+#    #+#             */
/*   Updated: 2021/01/14 16:40:39 by cquiana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			minishell_echo(char **cmd, t_data *data)
{
	int		i;

	if (cmd[1])
	{
		i = 1;
		if ((ft_compare_str(cmd[i], "-n")))
			i++;
		while (cmd[i] != NULL)
		{
			ft_putstr_fd(cmd[i], 1);
			if (cmd[i + 1])
				ft_putstr_fd(" ", 1);
			i++;
		}
		if (!(ft_compare_str(cmd[1], "-n")))
			ft_putstr_fd("\n", 1);
	}
	else
		ft_putstr_fd("\n", 1);
	return (g_status = 0);
}
