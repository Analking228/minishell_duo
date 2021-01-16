/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <cquiana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 16:29:57 by cjani             #+#    #+#             */
/*   Updated: 2021/01/13 15:48:25 by cquiana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			minishell_pwd(char **cmd, t_data *data)
{
	char	*pn;

	if (!(pn = getcwd(NULL, 0)))
	{
		g_status = 127;
		ft_error("getcwd error", 1);
	}
	else
	{
		ft_putstr_fd(pn, 1);
		ft_putstr_fd("\n", 1);
	}
	free(pn);
	return (g_status = 0);
}
