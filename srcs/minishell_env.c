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

/*without any options and any arguments*/

#include "../includes/minishell.h"

int			minishell_env(t_args *tab, t_data *data)
{
	int	i;
	int	close_out;

	i = 0;
	close_out = minishell_redirect_out(tab, data);
	while (data->envp[i])
	{
		ft_putstr_fd(data->envp[i], data->fd_out);
		ft_putchar_fd('\n', data->fd_out);
		i++;
	}
	if (close_out)
	{
		dup2(data->fd_1, 1);
		close(data->fd_1);
	}
	return (0);
}
