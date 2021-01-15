/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 11:05:09 by cquiana           #+#    #+#             */
/*   Updated: 2021/01/08 19:07:43 by cquiana          ###   ########.fr       */
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
		tmp = tab->next;
		if (tab->exec_path != NULL)
			free(tab->exec_path);
		if (tab->cmd)
			ft_free_double_array(tab->cmd);
		if (tmp == NULL)
			break ;
		tab = tmp->next;
	}
	free(tab);
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
