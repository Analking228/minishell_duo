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

int				minishell_redirect_out(t_args *tab, t_data *data)
{
	int			fd;

	if (tab->simbol == RLR)
	{
		fd = open(tab->next->cmd[0], O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
		data->fd_out = dup2(fd, 1);
		close(fd);
		return (1);
	}
	else if (tab->simbol == DRLR)
	{
		fd = open(tab->next->cmd[0], O_CREAT | O_RDWR | O_APPEND, S_IRWXU);
		data->fd_out = dup2(fd, 1);
		close(fd);
		return (1);
	}
	return (0);
}

int				minishell_redirect_in(t_args *tab, t_data *data)
{
	int			fd;

	if (tab->simbol == RLL)
	{
		fd = open(tab->next->cmd[0], O_RDONLY, S_IRUSR);
		data->fd_in = dup2(fd, 0);
		close(fd);
		return (1);
	}
	return (0);
}

static void		minishell_pipe_pipe(int *oldfd, int *newfd)
{
	pipe(newfd);
	dup2(newfd[W], 1);
	close(newfd[W]);
	dup2(oldfd[R], 0);
	close(oldfd[R]);
	oldfd[R] = newfd[R];
	oldfd[W] = newfd[W];
	return ;
}

void			minishell_pipe(t_args *tab, t_data *data)
{
	static int	oldfd[2];
	static int	newfd[2];

	if ((tab->simbol == PIPE) && (tab->simbol_last < PIPE))
	{
		pipe(newfd);
		dup2(newfd[W], 1);
		close(newfd[W]);
		oldfd[R] = newfd[R];
		oldfd[W] = newfd[W];
	}
	else if ((tab->simbol != PIPE) && (tab->simbol_last == PIPE))
	{
		dup2(oldfd[R], 0);
		close(oldfd[R]);
		dup2(data->fd_1, 1);
	}
	else if ((tab->simbol == PIPE) && (tab->simbol_last == PIPE))
	{
		minishell_pipe_pipe(oldfd, newfd);
	}
}

int				ft_compare_str(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] == str2[i])
	{
		i++;
		if (str1[i] == '\0' && str2[i] == '\0')
			return (1);
	}
	return (0);
}
