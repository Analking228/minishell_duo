/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 12:54:00 by cquiana           #+#    #+#             */
/*   Updated: 2021/01/11 13:58:06 by cquiana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}


char	*check_tail(char **tail, char **line)
{
	char *ptr_nl;

	ptr_nl = NULL;
	if (*tail)
	{
		if ((ptr_nl = ft_strchr(*tail, '\n')))
		{
			*ptr_nl = '\0';
			*line = ft_strdup(*tail);
			ft_strcpy(*tail, ++ptr_nl);
		}
		else
		{
			*line = ft_strdup(*tail);
			free(*tail);
			*tail = NULL;
		}
	}
	else
		*line = ft_strdup("");
	return (ptr_nl);
}

int		get_line(int fd, char **line)
{
	static char		*tail;
	char			buf[BUFFER_SIZE + 1];
	char			*ptr_nl;
	int				byte;

	if (fd < 0 || BUFFER_SIZE < 1 || !line || read(fd, buf, 0) < 0)
		return (-1);
	ptr_nl = check_tail(&tail, line);
	while (!ptr_nl && (byte = read(fd, buf, BUFFER_SIZE)) != -1)
	{
		if (!byte && !ft_strlen(*line))
			return (42);
		// else if (!byte)
		// 	ft_putstr_fd("  \b\b", 1);
		buf[byte] = '\0';
		if ((ptr_nl = ft_strchr(buf, '\n')))
		{
			*ptr_nl = '\0';
			free(tail);
			tail = ft_strdup(++ptr_nl);
		}
		*line = ft_strjoinf(*line, buf);
	}
	return (!byte && !ptr_nl) ? 0 : 1;
}
