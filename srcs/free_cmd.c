/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <cquiana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 11:05:09 by cquiana           #+#    #+#             */
/*   Updated: 2021/01/21 18:43:36 by cquiana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_free_double_array(char **cmd)
{
	int		i;

	i = 0;
	if (!cmd)
		return ;
	while (cmd[i])
	{
		free(cmd[i]);
		cmd[i] = NULL;
		i++;
	}
	free(cmd);
	cmd = NULL;
}

void		free_cmd(t_args *tab)
{
	t_args	*tmp;

	while (tab != NULL)
	{
		tmp = tab;
		tab = tmp->next;
		if (tmp->exec_path != NULL)
			free(tmp->exec_path);
		if (tmp->cmd)
			ft_free_double_array(tmp->cmd);
		free(tmp);
	}
}

t_pars		ft_reset(t_pars p)
{
	p.i++;
	p.c = 0;
	p.arr = NULL;
	return (p);
}

t_pars		ft_init_pars_sruc(void)
{
	t_pars	p;

	p.i = 0;
	p.c = 0;
	p.arg = NULL;
	p.arr = NULL;
	return (p);
}
