/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 21:43:01 by cquiana           #+#    #+#             */
/*   Updated: 2021/01/06 12:52:41 by cquiana          ###   ########.fr       */
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
	char	**tmp;

	i = 0;
	tmp = array;
	if (array == NULL)
	{
		array = (char **)malloc(sizeof(char*) * (size + 1));
		array[size] = NULL;
		return (array);
	}
	else
	{
		size += array_len(array);
		array = (char **)malloc(sizeof(char*) * (size + 1));
		while (i < size)
		{
			array[i] = tmp[i];
			i++;
		}
		array[i] = NULL;
	}
	return (array);
}
