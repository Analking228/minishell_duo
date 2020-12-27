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
	int	fd_out;

	while (tab)
	{
		fd_out = minishell_redirect_out(tab, data);
		if (!ft_strncmp(tab->cmd[0], "export", 6))
			minishell_export(tab, data, fd_out);
		else if (!ft_strncmp(tab->cmd[0], "echo", 4))
			minishell_echo(tab, data, fd_out);
		else if (!ft_strncmp(tab->cmd[0], "cd", 2))
			minishell_cd(tab, data);
		else if (!ft_strncmp(tab->cmd[0], "env", 3))
			minishell_env(data, fd_out);
		else if (!ft_strncmp(tab->cmd[0], "exit", 4))
			minishell_exit(tab, data);
		else if (!ft_strncmp(tab->cmd[0], "unset", 5))
			minishell_unset(tab, data);
		else if (!ft_strncmp(tab->cmd[0], "pwd", 3))
			minishell_pwd(data, fd_out);
		else if (tab->cmd[0])
			minishell_execve(tab, data, fd_out);
		close(fd_out);
		tab = tab->next;
	}
	return (0);
}