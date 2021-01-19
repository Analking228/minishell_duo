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

void		start_fd_closer(t_args *tab, t_data *data)
{
	if (tab->simbol < PIPE)
	{
		dup2(data->fd_1, 1);
		dup2(data->fd_0, 0);
	}
}

int			minishell_start(t_args *tab, t_data *data)
{
	while (tab)
	{
		minishell_pipe(tab, data);
		minishell_redirect_in(tab, data);
		minishell_redirect_out(tab, data);
		if (!ft_strncmp(tab->cmd[0], "export", 6))
			minishell_export(tab->cmd, data);
		else if (!ft_strncmp(tab->cmd[0], "cd", 2))
			minishell_cd(tab->cmd, data);
		else if (!ft_strncmp(tab->cmd[0], "echo", 4))
			minishell_echo(tab->cmd, data);
		else if (!ft_strncmp(tab->cmd[0], "env", 3))
			minishell_env(tab->cmd, data);
		else if (!ft_strncmp(tab->cmd[0], "pwd", 3))
			minishell_pwd(tab->cmd, data);
		else if (!ft_strncmp(tab->cmd[0], "exit", 4))
			minishell_exit(tab, data);
		else if (!ft_strncmp(tab->cmd[0], "unset", 5))
			minishell_unset(tab, data);
		else if (tab->cmd[0] && (tab->simbol_last < RLR))
			minishell_execve(tab, data);
		start_fd_closer(tab, data);
		tab = tab->next;
	}
	return (0);
}
