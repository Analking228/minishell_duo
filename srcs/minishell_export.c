/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 16:29:57 by cjani             #+#    #+#             */
/*   Updated: 2021/01/16 12:32:33 by cquiana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_existed(char *tmp, t_data *data)
{
	int		i;
	int		j;
	char	*c;

	if (tmp)
	{
		i = 0;
		while (data->envp[i])
		{
			if (minishell_export_str_prove(tmp, data->envp[i]))
				return (1);
			i++;
		}
	}
	return (0);
}

static char	**export_add(char **cmd, t_data *data, int add)
{
	int		i;
	int		j;
	char	**tmp;

	j = 1;
	i = ft_envp_count(data) + 1;
	tmp = data->envp;
	if (!(data->envp = (char **)ft_calloc(sizeof(char *), (i + add))))
		return (0);
	i = 0;
	while (tmp[i])
	{
		if (!minishell_export_str_prove(cmd[j], tmp[i]))
			data->envp[i] = ft_strdup(tmp[i]);
		else
			data->envp[i] = ft_strdup(cmd[j++]);
		free(tmp[i]);
		i++;
	}
	free(tmp[i]);
	free(tmp);
	while (add--)
		data->envp[i++] = ft_strdup(cmd[j++]);
	data->envp[i] = NULL;
	return (data->envp);
}

static char	*adding_breckets(char *str)
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
	int		i;
	char	*tmp;

	i = 0;
	while (data->envp[i])
	{
		tmp = adding_breckets(data->envp[i++]);
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(tmp, 1);
		ft_putchar_fd('\n', 1);
		free(tmp);
	}
}

int			minishell_export(char **cmd, t_data *data)
{
	int		i;
	int		j;

	i = 1;
	if (!cmd[i])
	{
		export_default(data);
		return (1);
	}
	j = 0;
	while (cmd[i])
	{
		if (!check_existed(cmd[i], data))
			j++;
		i++;
	}
	data->envp = export_add(cmd, data, j);
	return (1);
}
