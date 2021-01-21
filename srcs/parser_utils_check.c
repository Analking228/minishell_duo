/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <cquiana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 08:33:33 by cquiana           #+#    #+#             */
/*   Updated: 2021/01/21 20:36:24 by cquiana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char		*parse_envp(t_data *data, char *line, int *i)
{
	char	*key;
	char	*res;

	(*i)++;
	if (ft_strchr("0123456789 \"?\0", line[(*i)]))
	{
		res = dollar_cases(data, line, i);
		return (res);
	}
	if (!(key = ft_strdup("")))
		ft_error("malloc error\n", 2);
	key = ft_get_key(line, i, key);
	// key = add_symbol(key, '=');
	key = ft_strjoinf(key, "=");
	res = ft_env_value(key, data);
	free(key);
	key = NULL;
	return (res);
}

static void	ft_check_redirect(t_args *tab, t_data *data)
{
	t_args	*buf;
	t_args	*sym;
	char	*cmd;

	while (tab)
	{
		if (tab->simbol == RLR || tab->simbol == DRLR)
		{
			sym = tab;
			buf = tab->next;
			while (tab->simbol == RLR || tab->simbol == DRLR)
			{
				minishell_redirect_out(tab, data);
				start_fd_closer(tab, data);
				sym->simbol = tab->simbol;
				tab = tab->next;
			}
			cmd = tab->cmd[0];
			tab->cmd[0] = buf->cmd[0];
			buf->cmd[0] = cmd;
		}
		tab = tab->next;
	}
}

void		ft_check_list(t_args *tab, t_data *data, t_pars *p)
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
			save_sym[i++] = tmp->simbol;
			tmp = tmp->next;
		}
		ft_set_simbol(tab, save_sym);
		free(save_sym);
	}
	ft_check_redirect(tab, data);
	ft_free_pars_sruc(p);
}
