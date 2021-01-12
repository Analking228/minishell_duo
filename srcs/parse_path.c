/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 18:34:24 by cquiana           #+#    #+#             */
/*   Updated: 2021/01/12 15:09:33 by cquiana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			ft_skip_space(char *str, int i)
{
	while (str[i] == ' ')
		i++;
	return (i);
}

int			ft_is_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "echo", 4) || !ft_strncmp(cmd, "cd", 2) ||
		!ft_strncmp(cmd, "pwd", 3) || !ft_strncmp(cmd, "export", 6) ||
		!ft_strncmp(cmd, "unset", 5) || !ft_strncmp(cmd, "env", 3) ||
		!ft_strncmp(cmd, "exit", 4) || !ft_strncmp(cmd, "$?", 2))
		return (0);
	else
		return (1);
}

static int	find_exec_bin(char *path)
{
	struct stat	buf;
	int			value;

	value = lstat(path, &buf);
	return (value);
}

void		parse_exec_path(t_data *data, t_args *tab)
{
	char	*tmp;
	char	**split_path;
	int		i;

	i = 0;
	tmp = ft_strdup(ft_envp_srch_str("PATH", data) + 5);
	split_path = ft_split(tmp, ':');
	free(tmp);
	while (split_path[i] != 0)
	{
		tmp = ft_strjoin(split_path[i], "/");
		tmp = ft_strjoinf(tmp, tab->cmd[0]);
		if ((find_exec_bin(tmp) == 0))
		{
			tab->exec_path = ft_strdup(tmp);
			free(tmp);
			break ;
		}
		i++;
		free(tmp);
	}
	ft_free_double_array(split_path);
	split_path = NULL;
}
