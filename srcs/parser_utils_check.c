/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 08:33:33 by cquiana           #+#    #+#             */
/*   Updated: 2021/01/19 12:42:29 by cquiana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_check_redirect(t_args *tab, t_data *data)
{
	t_args	*tmp;
	t_args	*buf;
	t_args	*sym;
	char	*cmd;

	tmp = tab;
	while (tab)
	{
		if (tab->simbol == RLR || tab->simbol == DRLR)
		{
			sym = tab;
			buf = tab->next;
			while (tab->simbol == RLR || tab->simbol == DRLR)
			{
				sym->simbol = tab->simbol;
				tab = tab->next;
			}
			cmd = tab->cmd[0];
			tab->cmd[0] = buf->cmd[0];
			buf->cmd[0] = cmd;
		}
		tab = tab->next;
	}
	tab = tmp;
}

void		ft_check_list(t_args *tab, t_data *data)
{
	int		*save_sym;
	int		i;
	t_args	*tmp;

	if (!tab)
		return ;
	i = 0;
	if (tab->next == NULL)
		tab->simbol = 0;
	else
	{
		tab->simbol_last = 0;
		tmp = tab;
		if (!(save_sym = (int *)malloc(sizeof(int) * ft_list_len(tab))))
			ft_error("malloc error", 2);
		while (tmp)
		{
			save_sym[i] = tmp->simbol;
			tmp = tmp->next;
			i++;
		}
		ft_set_simbol(tab, save_sym);
		free(save_sym);
	}
	ft_check_redirect(tab, data);
}
