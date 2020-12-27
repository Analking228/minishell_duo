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

#include "../includes/minishell.h"

int			minishell_redirect_out(t_args *tab, t_data *data)
{
	int		fd;

	if (tab->simbol == RLR)
	{
		fd = open(tab->cmd[0], O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
		return (fd);
	}
	else if (tab->simbol == DRLR)
	{
		fd = open(tab->cmd[0], O_CREAT | O_RDWR | O_APPEND, S_IRWXU);
		return (fd);
	}
	return (dup(1));
}

int			minishell_redirect_pipe(t_args *tab, t_data *data)
{
	int		fd;
	
	if (tab->simbol == RLL)
	{
		fd = open(tab->cmd[0], O_CREAT | O_RDWR | O_APPEND, S_IRWXU);
		return (fd);
	}
	return (0);
}

