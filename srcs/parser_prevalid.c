/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_prevalid.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 11:34:50 by cquiana           #+#    #+#             */
/*   Updated: 2021/01/17 22:11:57 by cquiana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			is_space(char c)
{
	return (c == ' ');
}

static int	check_double_pipe_sem(char *line)
{
	if ((check_double_sem(line)) || (check_double_pipe(line)))
		return (1);
	return (0);
}

static void	ft_syntax_err(char c)
{
	if (c == ';')
		ft_putstr_fd("syntax error near unexpected token `;'\n", 2);
	else if (c == '|')
		ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
	else if (c == '>' || c == '<')
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
}

static void	ft_syntax_err2(char c)
{
	if (c == ';')
		ft_putstr_fd("syntax error near unexpected token `;;'\n", 2);
	else if (c == '|')
		ft_putstr_fd("syntax error near unexpected token `||'\n", 2);
}

void		validate_line(char *line)
{
	int		i;

	i = ft_skip_space(line, 0);
	if (!(ft_strncmp(line, "echo $?", 7)))
		return ;
	if ((ft_strchr(";|><", line[i])))
	{
		i++;
		if ((ft_strchr(";|", line[i])) && line[i] != '\0')
			ft_syntax_err2(line[i]);
		else
			ft_syntax_err(line[--i]);
		g_status = 258;
	}
	else if (check_double_pipe_sem(line))
		g_status = 258;
	else
		g_status = 0;
}
