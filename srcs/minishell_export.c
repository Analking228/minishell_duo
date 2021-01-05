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

static int	free_tmp(char **tmp, int count)
{
	while (count != -1)
	{
		free(tmp[count]);
		count--;
	}
	free(tmp);
	tmp = NULL;
	return (1);
}

static char	**export_add(t_args *tab, t_data *data, int add)
{
	int		i;
	int		j;
	char	**tmp;

	j = 1;
	i = ft_envp_count(data);
	tmp = data->envp;
	if (!(data->envp = (char **)ft_calloc(sizeof(char *), (i + add))))
		return (0);
	i = 0;
	while (tmp[i])
	{
		data->envp[i] = ft_strdup(tmp[i]);
		free(tmp[i]);
		i++;
	}
	free(tmp[i]);
	free(tmp);
	while (add)
	{
		data->envp[i++] = ft_strdup(tab->cmd[j++]); /* добавить проверку
													на знак равно */
		add--;
	}
	data->envp[i] = NULL;
	return (data->envp);
}

static char *adding_breckets(char *str)
{
	char	*tmp;
	int		i;

	tmp = ft_calloc(ft_strlen(str) + 3, sizeof(char));
	while (str[i] && (str[i - 1] != '='))
	{
		tmp[i] = str[i];
		i++;
	}
	if (str[i - 1] == '=')
	{
		tmp[i++] = '\"';
		while (str[i - 1])
		{
			tmp[i] = str[i - 1];
			i++;
		}
		tmp[i] = '\"';
	}
	return (tmp);
}

static void	export_default(t_data *data)
{
	int	i;
	char	*tmp;

	i = 0;
	while (data->envp[i])
	{
		tmp = adding_breckets(data->envp[i++]);
		ft_putstr_fd("declare -x ", data->fd_out);
		ft_putstr_fd(tmp, data->fd_out);
		ft_putchar_fd('\n', data->fd_out);
		free(tmp);
	}
}

int		minishell_export(t_args *tab, t_data *data)
{
	int	i;
	int	j;

	i = 1;
	if (!tab->cmd[i])
	{
		export_default(data);
		return (1);
	}
	j = 0;
	while (tab->cmd[i])
	{
		j++;
		i++;
	}
	data->envp = export_add(tab, data, j);
	return (1);
}