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

/*with option ’-n’*/

#include "../includes/minishell.h"

int			minishell_echo(char **cmd, t_data *data)
{
	int		i;

	if (cmd[1])
	{
		// printf("%d\n", data->fd_out);
		i = 1;
		if ((ft_strnstr(cmd[i], "-n", 3) && cmd[i][3] == 0))
			i++;
		while (cmd[i] != NULL)
		{
			ft_putstr_fd(cmd[i], 1);
			if (cmd[i + 1])
				ft_putstr_fd(" ", 1);
			i++;
		}
		if (!ft_strnstr(cmd[1], "-n", 2))
			ft_putstr_fd("\n", 1);
	}
	else
		ft_putstr_fd("\n", 1);
	return (0);
}
