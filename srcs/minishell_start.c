/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libasm.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjani <cjani@studen.21-school.ru>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 12:50:21 by flexer            #+#    #+#             */
/*   Updated: 2020/10/31 20:37:52 by cjani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		minishell_start(t_args *tab, t_data *data)
{
	int	*masfd[2];

	while (tab)
	{
		minishell_redirect_out(tab, data);
		minishell_redirect_pipe(tab, data);
		if (!ft_strncmp(tab->cmd[0], "export", 6))
			minishell_export(tab, data);
		else if (!ft_strncmp(tab->cmd[0], "echo", 4))
			minishell_echo(tab, data);
		else if (!ft_strncmp(tab->cmd[0], "cd", 2))
			minishell_cd(tab, data);
		else if (!ft_strncmp(tab->cmd[0], "env", 3))
			minishell_env(data);
		else if (!ft_strncmp(tab->cmd[0], "exit", 4))
			minishell_exit(tab, data);
		else if (!ft_strncmp(tab->cmd[0], "unset", 5))
			minishell_unset(tab, data);
		else if (!ft_strncmp(tab->cmd[0], "pwd", 3))
			minishell_pwd(data);
		else if (tab->cmd[0])
			minishell_execve(tab, data);
		tab = tab->next;
	}
	dup2(data->fd_1, 1);
	close(data->fd_1);
	dup2(data->fd_0, 0);
	close(data->fd_0);
	return (0);
}