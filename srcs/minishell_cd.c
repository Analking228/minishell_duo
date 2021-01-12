/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_cd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 16:29:57 by cjani             #+#    #+#             */
/*   Updated: 2021/01/12 11:03:05 by cquiana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*with only a relative or absolute path*/

#include "../includes/minishell.h"

static void		minishell_cd_addpwd(t_data *data)
{
	int			i;
	char		**tmp;
	// char		PathName[PATH_MAX];
	char		*path;

	i = 3;
	// if (!(getwd(PathName)))
	// 	ft_error("getwd error", data->fd_out);
	if (!(path = getcwd(NULL, 0)))
		ft_error("getwd error", data->fd_out);
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
	// char		PathName[PATH_MAX];
	char		*path;

	i = 3;
	// if (!(getwd(PathName)))
	// 	ft_error("getwd error", data->fd_out);
	if (!(path = getcwd(NULL, 0)))
		ft_error("getwd error", data->fd_out);
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

int		minishell_cd(char **cmd, t_data *data)
{
	minishell_cd_addoldpwd(data);
	chdir(cmd[1]);
	// ft_putendl_fd("error here, in addpwd", 1);
	minishell_cd_addpwd(data);
	return (0);
}
