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

/*with only a relative or absolute path*/

#include "../includes/minishell.h"

int		minishell_cd(t_args *tab, t_data *data)
{
	chdir(tab->cmd[1]);
	
	return (0);
}
/*
static void		minishell_cd_addpwd(t_data *data)
{
	int			i;

	while (data->envp[i])
	{
		i++;
	}
}*/