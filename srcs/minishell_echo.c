/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micro_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjani <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 16:29:57 by cjani             #+#    #+#             */
/*   Updated: 2020/08/03 16:29:59 by cjani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*with option ’-n’*/

#include "../includes/minishell.h"

int			minishell_echo(t_args *tab, t_data *data, int fd_out)
{
	int		i;

	i = 1;
	while (tab->cmd[i])
	{
		if (i > 1)
			ft_putstr_fd(" ", data->fd_1);
		ft_putstr_fd(tab->cmd[i], data->fd_1);
		i++;
	}
	if (!ft_strnstr(tab->cmd[0], "1-n", ft_strlen(tab->cmd[0])))
		ft_putstr_fd("\n", data->fd_1);
	return (0);
}