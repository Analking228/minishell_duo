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

/*with only a relative or absolute path*/

#include "../includes/minishell.h"

static void		minishell_cd_addpwd(t_data *data)
{
	int			i;
	char		**tmp;
	char		PathName[PATH_MAX];

	i = 3;
	if (!(getwd(PathName)))
		ft_error("getwd error", data->fd_out);
	tmp = (char **)ft_calloc(sizeof(char *), i);
	tmp[0] = ft_strdup("export");
	tmp[1] = ft_strjoin("PWD=", PathName);
	minishell_export(tmp, data);
	free(tmp[2]);
	free(tmp[1]);
	free(tmp[0]);
	free(tmp);
}

static void		minishell_cd_addoldpwd(t_data *data)
{
	int			i;
	char		**tmp;
	char		PathName[PATH_MAX];

	i = 3;
	if (!(getwd(PathName)))
		ft_error("getwd error", data->fd_out);
	tmp = (char **)ft_calloc(sizeof(char *), i);
	tmp[0] = ft_strdup("export");
	tmp[1] = ft_strjoin("OLDPWD=", PathName);
	minishell_export(tmp, data);
	free(tmp[2]);
	free(tmp[1]);
	free(tmp[0]);
	free(tmp);
}

int		minishell_cd(char **cmd, t_data *data)
{
	minishell_cd_addoldpwd(data);
	chdir(cmd[1]);
	ft_putendl_fd("error here, in addpwd", 1);
	minishell_cd_addpwd(data);
	return (0);
}