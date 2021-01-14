/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_prevalid2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 17:04:25 by cquiana           #+#    #+#             */
/*   Updated: 2021/01/14 17:04:52 by cquiana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_double_pipe(char *line)
{
	int		i;

	i = 0;
	while (is_space(line[i]) || ft_isalpha(line[i]))
		i++;
	if (line[i] == '|')
	{
		i++;
		while (is_space(line[i]))
			i++;
		if (line[i] == '|')
		{
			ft_putstr_fd("syntax error near unexpected token `|'\n", 1);
			return (1);
		}
	}
	return (0);
}

int	check_double_sem(char *line)
{
	int	i;

	i = 0;
	while (is_space(line[i]) || ft_isalpha(line[i]))
		i++;
	if (line[i] == ';')
	{
		i++;
		if (line[i] == ';')
		{
			ft_putstr_fd("syntax error near unexpected token `;;'\n", 1);
			return (1);
		}
		else
		{
			while (is_space(line[i]))
				i++;
			if (line[i] == ';')
			{
				ft_putstr_fd("syntax error near unexpected token `;'\n", 1);
				return (1);
			}
		}
	}
	return (0);
}
