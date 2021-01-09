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
	static int		pipefd[2];

	if ((tab->simbol == PIPE) && !data->opnd_pipe)
	{
		pipe(pipefd);
		data->opnd_pipe = 1;
	}
	if ((tab->simbol == PIPE) && (tab->simbol_last < PIPE))
	{
		data->fd_1 = dup(1);
		data->pipe_fd[1] = dup2(pipefd[W], 1);
		close(pipefd[W]);
	}
	else if((tab->simbol < PIPE) && (tab->simbol_last == PIPE))
	{
		close(data->pipe_fd[1]);
		data->fd_out = dup2(data->fd_1, 1);
		data->pipe_fd[1] = -1;
		data->fd_0 = dup(0);
		data->pipe_fd[0] = dup2(pipefd[R], 0);
		close(pipefd[R]);
		data->opnd_pipe = 0;
	}
	else if((tab->simbol == PIPE) && (tab->simbol_last == PIPE))
	{
		data->fd_0 = dup(0);
		data->pipe_fd[0] = dup2(pipefd[R], 0);
	}
}

