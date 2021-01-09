/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 16:29:57 by cjani             #+#    #+#             */
/*   Updated: 2021/01/02 14:15:42 by cquiana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_env_srch_len(char *str)
{
	int		count;

	count = 0;
	while (*str)
	{
		if (*str == '=')
			return (count);
		count++;
		str++;
	}
	return	(count);
}

int			ft_envp_srch(char *envp_name, t_data *data)
{
	int		i;
	int		res;
	int		len;

	i = 0;
	res = -1;
	while (data->envp[i])
	{
		len = ft_env_srch_len(data->envp[i]);
		if ((ft_strnstr(data->envp[i], envp_name, len)))
		{
			return (res = i);
		}
		i++;
	}
	return (res);
}

char			*ft_envp_srch_str(char *envp_name, t_data *data)
{
	int		i;
	char	*res;
	int		len;

	i = 0;
	res = NULL;
	while (data->envp[i])
	{
		len = ft_env_srch_len(data->envp[i]);
		if ((res = ft_strnstr(data->envp[i], envp_name, len)))
		{
			return (res);
		}
		i++;
	}
	return (res);
}

void	ft_init_struct(t_args *tab, t_data *data)
{
	data->envp = NULL;
	data->exec_code = 0;
	data->oldpwd = NULL;
	data->curpwd = NULL;
	data->fd_0 = 0;
	data->fd_1 = 1;
	data->fd_out = data->fd_1;
	data->fd_in = data->fd_0;
	data->pipe_fd[0] = -1;
	data->pipe_fd[1] = -1;
	data->opnd_pipe = 0;
}

int		ft_envp_count(t_data *data)
{
	int	i;

	i = 0;
	while (data->envp[i])
		i++;
	return (i);
}

int		ft_crt_envp(t_data *data, char **env)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
		i++;
	j = 0;
	if (!(data->envp = (char **)malloc(sizeof(char *) * (i + 1))))
		ft_error("malloc failed\n", 1);
	while (j != i)
	{
		data->envp[j] = ft_strdup(env[j]);
		j++;
	}
	data->envp[j] = NULL;
	data->curpwd = ft_strdup(ft_envp_srch_str("PWD", data) + 4);
	//printf("curpwd = %s\n", data->curpwd);
	data->oldpwd = ft_strdup(ft_envp_srch_str("PWD", data) + 4);
	return (0);
}
