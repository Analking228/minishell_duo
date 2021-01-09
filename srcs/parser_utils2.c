/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <cquiana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 17:19:10 by cquiana           #+#    #+#             */
/*   Updated: 2021/01/09 17:21:38 by cquiana          ###   ########.fr       */
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