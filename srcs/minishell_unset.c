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

static int	unset_remover(int count, t_data *data)
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

static int	unset_srch_len(char *envp_n)
{
	int		i;

	i = 0;
	while (envp_n[i] && envp_n[i] != '=')
		i++;
	return (i);
}

static int	unset_pos_checker(char *envp_n, t_data *data)
{
	int		i;
	int		len;
	int		j;

	i = 0;
	while (data->envp[i])
	{
		j = 0;
		len = unset_srch_len(data->envp[i]) - 1;
		while ((j < len) && envp_n[j])
		{
			if (data->envp[i][j] != envp_n[j])
			{
				break ;
			}
			j++;
		}
		if (data->envp[i][j] == envp_n[j])
			return (i);
		i++;
	}
	return (-1);
}

int			minishell_unset(t_args *tab, t_data *data)
{
	char	*srch_arg;
	int		i;
	int		count;

	i = 1;
	count = ft_args_valid(tab->cmd);
	if (count)
	{
		ft_putstr_fd("unset: ", 1);
		ft_putstr_fd(tab->cmd[count], 1);
		ft_putendl_fd(" : not a valid identifier\n", 1);
		return (g_status = 1);
	}
	while (tab->cmd[i])
	{
		srch_arg = tab->cmd[i];
		if ((count = unset_pos_checker(srch_arg, data)) > -1)
		{
			unset_remover(count, data);
		}
		i++;
	}
	return (0);
}
