/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <cquiana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 16:29:57 by cjani             #+#    #+#             */
/*   Updated: 2021/01/09 16:25:11 by cquiana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			main(int argc, char **argv, char **env)
{
	t_args	*tab;
	t_data	*data;
	char	*line;

	(void)argc;
	(void)argv;
	data = ft_crt_envp(env);
	while (1)
	{
		ft_putstr_fd(">>> ", 1);
		get_next_line(0, &line);
		validate_line(line, data);
		tab = parse_input(line, tab, data);
		free(line);
		line = NULL;
		minishell_start(tab, data);
		free_cmd(tab);
		tab = NULL;
	}
	return (0);
}

