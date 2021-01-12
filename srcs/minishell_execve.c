/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_execve.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 16:29:57 by cjani             #+#    #+#             */
/*   Updated: 2021/01/12 17:42:28 by cquiana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		minishell_execve(t_args *tab, t_data *data)
{
	pid_t	pid;
	int		pipefd[2];
	int		ret;


	pid = fork();
	if (pid < 0)
		perror(NULL);
	else if (pid == 0)
	{
		ret = execve(tab->exec_path, tab->cmd, data->envp);
		if (ret == -1)
			ft_putstr_fd("Command not found\n", 2);
		exit(data->exec_code);
	}
	else
	{
		wait(&pid);
		data->exec_code = WEXITSTATUS(pid);
	}
	return (0);
}
