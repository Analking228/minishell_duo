/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_start.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 12:50:21 by cjani             #+#    #+#             */
/*   Updated: 2021/01/06 20:05:42 by cquiana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void start_fd_closer(t_data *data)
{
	//printf("data->fd_0 = %d\n", data->fd_0);
	if ((data->fd_1 != 1) && (data->pipe_fd[1] == -1))
	{
		dup2(data->fd_1, 1);
		close(data->fd_1);
		data->fd_1 = 1;
	}
	if ((data->fd_0 != 0) && (data->pipe_fd[0] == -1))
	{
		dup2(data->fd_0, 0);
		close(data->fd_0);
		data->fd_0 = 0;
	}
	if (!(data->opnd_pipe) && (data->pipe_fd[0] != -1))
	{
		close(data->pipe_fd[0]);
		data->fd_in = dup2(data->fd_0, 0);
		close(data->fd_0);
		data->fd_0 = 0;
		data->pipe_fd[0] = -1;
	}
	if (!(data->opnd_pipe) && (data->pipe_fd[1] != -1))
	{
		close(data->pipe_fd[1]);
		data->fd_out = dup2(data->fd_1, 1);
		close(data->fd_1);
		data->fd_1 = 1;
		data->pipe_fd[1] = -1;
	}
}

int		minishell_start(t_args *tab, t_data *data)
{
	int	*masfd[2];

	while (tab)
	{
		//printf("simbol = %d\nsimbol_last = %d\n", tab->simbol, tab->simbol_last);
		minishell_pipe(tab, data);
		minishell_redirect_in(tab, data);
		minishell_redirect_out(tab, data);
		if (!ft_strncmp(tab->cmd[0], "export", 6))
			minishell_export(tab, data);
		else if (!ft_strncmp(tab->cmd[0], "echo", 4))
			minishell_echo(tab, data);
		else if (!ft_strncmp(tab->cmd[0], "cd", 2))
			minishell_cd(tab, data);
		else if (!ft_strncmp(tab->cmd[0], "env", 3))
			minishell_env(tab, data);
		else if (!ft_strncmp(tab->cmd[0], "exit", 4))
			minishell_exit(tab, data);
		else if (!ft_strncmp(tab->cmd[0], "unset", 5))
			minishell_unset(tab, data);
		else if (!ft_strncmp(tab->cmd[0], "pwd", 3))
			minishell_pwd(tab, data);
		else if (tab->cmd[0] && (tab->simbol_last < RLR))
			minishell_execve(tab, data);
		start_fd_closer(data);
		tab = tab->next;
	}
	return (0);
}
