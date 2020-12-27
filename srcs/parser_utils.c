/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 21:43:01 by cquiana           #+#    #+#             */
/*   Updated: 2020/12/14 21:44:26 by cquiana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char    *add_symbol(char *str, char c)
{
    char    *res;
    int     i;

    i = 0;
    res = (char *)malloc(sizeof(char) * (ft_strlen(str) + 2)); // if
    while (str[i])
    {
        res[i] = str[i];
        i++;
    }
    res[i++] = c;
    res[i] = '\0';
    free(str);
    return (res);
}

char	**double_array_realloc(char **array, int size)
{
	int		i;
	int		len;
	char	**tmp;

	i = 0;
	len = 0;
	tmp = array;
	if (!array)
	{
		array = (char **)malloc(sizeof(char*) * (size + 1));
		array[size] = NULL;
	}
	else
	{
		while (array[len])
			len++;
		size += len;
		array = (char **)malloc(sizeof(char*) * (size + 1));
		while (i < size)
		{
			array[i] = tmp[i];
			i++;
		}
		array[i] = NULL;
		free(tmp);
	}
	return (array);
}
