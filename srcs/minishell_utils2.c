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
#define W 1
#define R 0

int			minishell_redirect_out(t_args *tab, t_data *data)
{
	int		fd;

	if (tab->simbol == RLR)
	{
		data->fd_1 = dup2(1, 4);
		fd = open(tab->next->cmd[0], O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
		data->fd_out = dup2(fd, 1);
		close(fd);
		return (data->fd_out);
	}
	else if (tab->simbol == DRLR)
	{
		data->fd_1 = dup2(1, 4);
		fd = open(tab->next->cmd[0], O_CREAT | O_RDWR | O_APPEND, S_IRWXU);
		data->fd_out = dup2(fd, 1);
		close(fd);
		return (data->fd_out);
	}
	return (0);
}

int			minishell_redirect_pipe(t_args *tab, t_data *data)
{
	int		pipefd[2];
	int		fd;
	
	if (data->fd_1 == 1)
	{
		if ((tab->simbol == PIPE) || (tab->simbol_last == PIPE))
		{
			pipe(pipefd);
			data->fd_1 = dup(1);
			data->fd_0 = dup(0);
			data->fd_in = dup2(pipefd[R], 0);
			close(pipefd[R]);
			data->fd_out = dup2(pipefd[W], 1);
			close(pipefd[W]);
		}
		else if (tab->simbol == RLL)
		{
			data->fd_1 = dup2(1, 4);
			data->fd_0 = dup2(0, 3);
			fd = open(tab->next->cmd[0], O_RDONLY, S_IRUSR);
			data->fd_in = dup2(fd, 0);
		}
	}
	else if ((tab->simbol == SMCLN) && (tab->simbol_last == PIPE))
	{
		close(data->fd_out);
		data->fd_out = dup2(data->fd_1, 1);
	}
	return (0);
}

