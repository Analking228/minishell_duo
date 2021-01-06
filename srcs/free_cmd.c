/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 11:05:09 by cquiana           #+#    #+#             */
/*   Updated: 2021/01/06 14:46:21 by cquiana          ###   ########.fr       */
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
}

void		free_cmd(t_args *tab)
{
	t_args	*tmp;

	while (tab != NULL)
	{
		tmp = tab->next;
		if (tab->exec_path != NULL)
			free(tab->exec_path);
		ft_free_double_array(tab->cmd);
		if (tmp == NULL)
			break;
		tab = tmp->next;
	}
	free(tab);
}
