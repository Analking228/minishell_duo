/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_prevalid.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 11:34:50 by cquiana           #+#    #+#             */
/*   Updated: 2021/01/12 22:03:18 by cquiana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			is_space(char c)
{
	return (c == ' ');
}

static int	check_double_pipe(char *line)
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

static int	check_double_sem(char *line)
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

static int	check_double_pipe_sem(char *line)
{
	if ((check_double_sem(line)) || (check_double_pipe(line)))
		return (1);
	return (0);
}

void		ft_valid_error(char c)
{
	ft_putstr_fd("syntax error near unexpected token \'", 1);
	ft_putchar_fd(c, 1);
	ft_putstr_fd("\'\n", 1);
	gl_status = 258;
}

void		validate_line(char *line, t_data *data)
{
	int		i;

	i = ft_skip_space(line, 0);
	if (!(ft_strncmp(line, "echo $?", 7)))
		return ;
	if (line[i] == ';')
	{
		i++;
		if (line[i] == ';')
		{
			ft_putstr_fd("syntax error near unexpected token `;;'\n", 1);
			gl_status = 258;
			return ;
		}
		// ft_valid_error(line[i]);
		ft_putstr_fd("syntax error near unexpected token `;'\n", 1);
		gl_status = 258;
		i = ft_skip_space(line, 0);
	}
	else if (line[i] == '|')
	{
		if (line[i + 1] == '|')
			ft_putstr_fd("syntax error near unexpected token `||'\n", 1);
		else
			ft_putstr_fd("syntax error near unexpected token `|'\n", 1);
		// gl_status = 258;
	}
	else if (check_double_pipe_sem(line))
		gl_status = 258;
	else
		gl_status = 0;
}
