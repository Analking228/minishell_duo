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
	int	close_out;
	int	close_in;

	while (tab)
	{
		//printf("simbol_last = %d\n", tab->simbol_last);
		close_in = minishell_redirect_pipe(tab, data);
		close_out = minishell_redirect_out(tab, data);
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
		else if (tab->cmd[0] /*&& (tab->simbol_last < RLR)*/)
			minishell_execve(tab, data);
		if (close_in || close_out)
			tab = tab->next;
		if (close_out)
		{
			dup2(data->fd_1, 1);
			close(data->fd_1);
		}
		if (close_in)
		{
			dup2(data->fd_0, 0);
			close(data->fd_0);
		}
		tab = tab->next;
	}
	return (0);
}