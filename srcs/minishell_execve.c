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

int		minishell_execve(t_args *tab, t_data *data)
{
	pid_t	pid;
	int		pipefd[2];
	int	close_out;

	//minishell_redirect_pipe();
	close_out = minishell_redirect_out(tab, data);
	pid = fork();
	if (pid < 0)
		perror(NULL);
	else if (pid == 0)
	{
		execve(tab->exec_path, tab->cmd, data->envp);
		exit(data->exec_code);
	}
	else
	{
		wait(&pid);
		if (close_out)
	{
			dup2(data->fd_1, 1);
			close(data->fd_1);
	}
		data->exec_code = WEXITSTATUS(pid);
	}
	return (0);
}
