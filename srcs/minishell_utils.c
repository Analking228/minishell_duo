/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 16:29:57 by cjani             #+#    #+#             */
/*   Updated: 2021/01/16 11:04:52 by cquiana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

char		*ft_envp_srch_str(char *envp_name, t_data *data)
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

void		ft_init_struct(t_data *data)
{
	data->envp = NULL;
	data->fd_0 = dup(0);
	data->fd_1 = dup(1);
	data->fd_out = data->fd_1;
	data->fd_in = data->fd_0;
	read_status = 1;
	gl_status = 0;
}

int			ft_envp_count(t_data *data)
{
	int		i;

	i = 0;
	while (data->envp[i])
		i++;
	return (i);
}

t_data		*ft_crt_envp(char **env)
{
	int		i;
	int		j;
	t_data	*data;

	if (!(data = (t_data *)malloc(sizeof(t_data))))
		return (NULL);
	ft_init_struct(data);
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
	return (data);
}
