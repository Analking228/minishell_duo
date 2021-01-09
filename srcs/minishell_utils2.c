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
#define W 1
#define R 0

int			minishell_redirect_out(t_args *tab, t_data *data)
{
	int		fd;

	if (tab->simbol == RLR)
	{
		data->fd_1 = dup(1);
		fd = open(tab->next->cmd[0], O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
		data->fd_out = dup2(fd, 1);
		close(fd);
		return (data->fd_out);
	}
	else if (tab->simbol == DRLR)
	{
		data->fd_1 = dup(1);
		fd = open(tab->next->cmd[0], O_CREAT | O_RDWR | O_APPEND, S_IRWXU);
		data->fd_out = dup2(fd, 1);
		close(fd);
		return (data->fd_out);
	}
	return (0);
}

int			minishell_redirect_in(t_args *tab, t_data *data)
{
	int		fd;

	if (tab->simbol == RLL)
	{
		data->fd_0 = dup(0);
		fd = open(tab->next->cmd[0], O_RDONLY, S_IRUSR);
		data->fd_in = dup2(fd, 0);
		close(fd);
		return (1);
	}
	return (0);
}

void			minishell_pipe(t_args *tab, t_data *data)
{
	static int		oldfd[2];
	static int		newfd[2];

	if ((tab->simbol == PIPE) && (tab->simbol_last < PIPE))
	{
		pipe(newfd);
		dup2(newfd[W], 1);
		close(newfd[W]);
		oldfd[R] = newfd[R];
		oldfd[W] = newfd[W];
	}
	else if((tab->simbol < PIPE) && (tab->simbol_last == PIPE))
	{
		dup2(oldfd[R], 0);
		close(oldfd[R]);
		dup2(data->fd_1, 1);
	}
}

