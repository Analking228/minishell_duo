/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <cquiana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 16:29:57 by cjani             #+#    #+#             */
/*   Updated: 2021/01/13 15:49:49 by cquiana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*without any options and any arguments*/

#include "../includes/minishell.h"

int			minishell_env(char **cmd, t_data *data)
{
	int	i;

	i = 0;
	while (data->envp[i])
	{
		ft_putstr_fd(data->envp[i], data->fd_out);
		ft_putchar_fd('\n', data->fd_out);
		i++;
	}
	return (0);
}
