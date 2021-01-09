/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_echo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 16:29:57 by cjani             #+#    #+#             */
/*   Updated: 2021/01/02 14:16:12 by cquiana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*with option ’-n’*/

#include "../includes/minishell.h"

int			minishell_echo(t_args *tab, t_data *data)
{
	int		i;

	if (tab->cmd[1])
	{
		i = 1;
		if ((ft_strnstr(tab->cmd[1], "-n", 2) && tab->cmd[1][3] == 0))
			i++;
		while (tab->cmd[i])
		{
			ft_putstr_fd(tab->cmd[i], data->fd_out);
			if (tab->cmd[++i] != NULL)
				ft_putstr_fd(" ", data->fd_out);
		}
		if (!(ft_strnstr(tab->cmd[1], "-n", 2) && !tab->cmd[1]))
			ft_putstr_fd("\n", data->fd_out);
	}
	else
		ft_putstr_fd("\n", data->fd_out);
	return (0);
}
