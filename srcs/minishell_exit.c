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

void		ft_exit_error_neg_digit(t_args *tab)
{
	int		code;

	code = ft_atoi(tab->cmd[1]);
	if (code < 0 && code >= -256)
	{
		code = 256 + code;
		ft_putendl_fd("exit", 1);
		exit(code);
	}
	else if (code < -265)
	{
		code *= -1;
		code %= 256;
		code = 256 - code;
		ft_putendl_fd("exit", 1);
		exit(code);
	}
}

void		minishell_tabs_free(t_args *tab, t_data *data)
{
	int		i;

	i = ft_envp_count(data);
	free_cmd(tab);
	while (i)
		free(data->envp[i--]);
	free(data->envp[i]);
	free(data->envp);
	close(data->fd_0);
	close(data->fd_1);
	free(data);
}

void		ft_exit_error_digit(t_args *tab)
{
	int		code;

	code = ft_atoi(tab->cmd[1]);
	if (code >= 0 && code <= 255)
	{
		ft_putendl_fd("exit", 1);
		exit(code);
	}
	else if (code >= 256)
	{
		code %= 256;
		ft_putendl_fd("exit", 1);
		exit(code);
	}
}

void		ft_exit_error_alpha(t_args *tab)
{
	ft_putendl_fd("exit", 1);
	ft_putstr_fd(tab->cmd[1], 1);
	ft_putendl_fd(": numeric argument required", 1);
	exit(255);
}

int			minishell_exit(t_args *tab, t_data *data)
{
	if (!(tab->cmd[1]))
	{
		minishell_tabs_free(tab, data);
		ft_putendl_fd("exit", 1);
		exit(0);
	}
	else
	{
		if (tab->cmd[2])
		{
			g_status = 1;
			ft_putendl_fd("exit", 1);
			ft_putendl_fd("exit: too many arguments", 1);
		}
		else
		{
			if (ft_isalpha(tab->cmd[1][0]))
				ft_exit_error_alpha(tab);
			else if (ft_isdigit(tab->cmd[1][0]))
				ft_exit_error_digit(tab);
			else if (tab->cmd[1][0] == '-')
				ft_exit_error_neg_digit(tab);
		}
	}
	return (1);
}
