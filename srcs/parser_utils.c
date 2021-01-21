/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <cquiana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 21:43:01 by cquiana           #+#    #+#             */
/*   Updated: 2021/01/21 19:15:36 by cquiana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*add_symbol(char *str, char c)
{
	char	*res;
	int		i;

	i = 0;
	if (!(res = (char *)malloc(sizeof(char) * (ft_strlen(str) + 2))))
		ft_error("malloc error", 2);
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
		free(tmp);
		array[i] = NULL;
	}
	return (array);
}

char	**ft_crt_arr(char **arr, char *str, int *i)
{
	arr = double_array_realloc(arr, 1);
	arr[(*i)] = ft_strdup(str);
	(*i)++;
	return (arr);
}
