/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_prevalid.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <cquiana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 11:34:50 by cquiana           #+#    #+#             */
/*   Updated: 2021/01/09 12:22:25 by cquiana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int     is_space(char c)
{
    return (c == ' ');
}


void    check_double_pipe_sem(char *line)
{
    int     i;

    i = 0;
    while (is_space(line[i]) || ft_isalpha(line[i]))
        i++;
    if (line[i] == ';')
    {
        i++;
        if (line[i] == ';')
            ft_putstr_fd("syntax error near unexpected token `;;'\n", 1);
        else
        {
            while (is_space(line[i]))
                i++;
            if (line[i] == ';')
                ft_putstr_fd("syntax error near unexpected token `;'\n", 1);
        }
    }
}

void    validate_line(char *line)
{
    int     i;

    i = 0;
    while (is_space(line[i]))
        i++;
    if (line[i] == ';')
    {
        if (line[i + 1] == ';')
            ft_putstr_fd("syntax error near unexpected token `;;'\n", 1);
        else
            ft_putstr_fd("syntax error near unexpected token `;'\n", 1); // error
    }
    if (line[i] == '|')
    {
        if (line[i + 1] == '|')
            ft_putstr_fd("syntax error near unexpected token `||'\n", 1);
        else
            ft_putstr_fd("syntax error near unexpected token `|'\n", 1); // error
    }
    if (ft_isalpha(line[i]))
        check_double_pipe_sem(line);
}