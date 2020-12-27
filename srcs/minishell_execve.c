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

int		minishell_execve(t_args *tab, t_data *data, int fd_out)
{
	/*pid_t	pid;
	int		status;
	int		pipefd[2];

	minishell_redirect_pipe();
	status = 0;
	pid = fork();
	if (pid < 0)
		perror(NULL);
	else if (pid == 0)
	{
		execve(tab->exec_path, tab->cmd + 1, data->envp);
		exit(ft_atoi(all->error));
	}
	else
	{
		wait(&pid);
		status = WEXITSTATUS(pid);
		free(all->error);
		all->error = ft_itoa(status);
	}*/
	return (0);
}
