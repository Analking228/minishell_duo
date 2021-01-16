/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_cd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <cquiana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 16:29:57 by cjani             #+#    #+#             */
/*   Updated: 2021/01/13 16:14:29 by cquiana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void		minishell_cd_addpwd(t_data *data)
{
	int			i;
	char		**tmp;
	char		*path;

	i = 3;
	if (!(path = getcwd(NULL, 0)))
		ft_error("getwd error", 1);
	tmp = (char **)ft_calloc(sizeof(char *), i);
	tmp[0] = ft_strdup("export");
	tmp[1] = ft_strjoin("PWD=", path);
	minishell_export(tmp, data);
	free(tmp[2]);
	free(tmp[1]);
	free(tmp[0]);
	free(tmp);
	free(path);
}

static void		minishell_cd_addoldpwd(t_data *data)
{
	int			i;
	char		**tmp;
	char		*path;

	i = 3;
	if (!(path = getcwd(NULL, 0)))
		ft_error("getwd error", 1);
	tmp = (char **)ft_calloc(sizeof(char *), i);
	tmp[0] = ft_strdup("export");
	tmp[1] = ft_strjoin("OLDPWD=", path);
	minishell_export(tmp, data);
	free(tmp[2]);
	free(tmp[1]);
	free(tmp[0]);
	free(tmp);
	free(path);
}

int				minishell_cd(char **cmd, t_data *data)
{
	int			ret;

	minishell_cd_addoldpwd(data);
	ret = chdir(cmd[1]);
	if (ret == -1 && cmd[1] != NULL)
	{
		g_status = 1;
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putstr_fd("\n", 2);
	}
	minishell_cd_addpwd(data);
	return (g_status = 0);
}
