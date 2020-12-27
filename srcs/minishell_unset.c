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

/*without any options*/

#include "../includes/minishell.h"

static int			unset_remover(int count, t_data *data)
{
	int		i;
	char	*tmp;
	
	i = 0;
	while (i != count)
		i++;
	while (data->envp[i])
	{
		tmp = data->envp[i];
		if (data->envp[i + 1])
			data->envp[i] = ft_strdup(data->envp[i + 1]);
		else
			data->envp[i] = data->envp[i + 1];
		free(tmp);
		i++;
	}
	free(data->envp[i]);
	return (1);
}

int			minishell_unset(t_args *tab, t_data *data)
{
	char	*srch_arg;
	int		i;
	int		count;

	i = 1;
	while (tab->cmd[i])
	{
		srch_arg = tab->cmd[i];
		if ((count = ft_envp_srch(srch_arg, data)) > -1)
		{
			unset_remover(count, data);
		}
		i++;
	}
	return (1);
}