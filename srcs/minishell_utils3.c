/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 16:29:57 by cjani             #+#    #+#             */
/*   Updated: 2021/01/06 17:56:15 by cquiana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			ft_env_srch_len(char *str)
{
	int		count;

	count = 0;
	while (*str)
	{
		if ((*str == '=') || (*str == 0))
			return (count);
		count++;
		str++;
	}
	return (count);
}

int			minishell_str_prove_hard(char *str1, char *str2)
{
	int		i;

	if (str1)
	{
		i = 0;
		while (((str1[i] == str2[i])) && (str1[i] && str2[i]) &&
		(str1[i] != '=' && str2[i] != '='))
			i++;
		if ((str1[i] == '=') && (str2[i] == '='))
			return (1);
		if ((!str1[i]) && str2[i] == '=')
			return (1);
		if ((!str2[i]) && str1[i] == '=')
			return (1);
		if (!str1[i] && !str2[i])
			return (1);
	}
	return (0);
}

int			minishell_str_prove_soft(char *str1, char *str2)
{
	int		i;

	if (str1)
	{
		i = 0;
		while (((str1[i] == str2[i])) && (str1[i] && str2[i]) &&
		(str1[i] != '=' && str2[i] != '='))
			i++;
		if ((str1[i] == '=') && (str2[i] == '='))
			return (1);
		if ((!str2[i]) && str1[i] == '=')
			return (1);
	}
	return (0);
}

int			ft_check_arg(char *arg)
{
	int		i;

	i = 0;
	if (arg == NULL)
		return (0);
	if (arg[0] == '=')
		return (1);
	i++;
	while (arg[i] != '=' && arg[i])
	{
		if (!((ft_isalpha(arg[i]) || ft_isdigit(arg[i])) ||
		arg[i] == '_'))
			return (1);
		i++;
	}
	return (0);
}

int			ft_args_valid(char **args)
{
	int		i;

	i = 1;
	while (args[i])
	{
		if ((ft_check_arg(args[i])))
			return (i);
		i++;
	}
	return (0);
}
