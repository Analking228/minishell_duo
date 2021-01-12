/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 17:19:10 by cquiana           #+#    #+#             */
/*   Updated: 2021/01/12 14:47:29 by cquiana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int     ft_list_len(t_args *tab)
{
    int     len;
    t_args  *tmp;

    len = 0;
    tmp = tab;
    while (tmp)
    {
        tmp = tmp->next;
        len++;
    }
    return (len);
}

int     array_len(char **array)
{
    int     i;

    i = 0;
    while (array[i])
        i++;
    return (i);
}

void    ft_set_simbol(t_args *tab, int *save_sym)
{
    int     i;
    t_args  *tmp;

    tab->simbol_last = 0;
    tmp = tab->next;
    i = 0;
    while (tmp)
    {
        tmp->simbol_last = save_sym[i];
        tmp = tmp->next;
        i++;
    }
}

char	*ft_strjoinf(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*newstr;

	if (!s1 || !s2)
		return (NULL);
	if (!(newstr = malloc(sizeof(char) *
        ((ft_strlen((char*)s1) + ft_strlen((char*)s2)) + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		newstr[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		newstr[i] = s2[j];
		i++;
		j++;
	}
	newstr[i] = '\0';
    free((void *)s1);
	return (newstr);
}
