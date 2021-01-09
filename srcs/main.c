/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <cquiana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 16:29:57 by cjani             #+#    #+#             */
/*   Updated: 2021/01/09 11:42:14 by cquiana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

	/* Общее начало. Часть закомменченная - начало твоей парсерной части.
	Здесь нужно будет постоянно считывать вводимые данные и парсить их,
	чтобы в дальнейшем я мог ими воспользоваться. Указал в неплохом виде,
	будут какие-то изменения - обязательно оставляй коммент. Название
	твоих файлов и функций прошу начинать с "parser_"					*/

static int	free_tmp(char **tmp, int count)
{
	//ft_printf("in the free\n");
	while (count)
	{
		//ft_printf("freeing %d %s\n", count, tmp[count]);
		free(tmp[count]);
		count--;
	}
	free(tmp);
	return (1);
}

int			main(int argc, char **argv, char **env)
{
	t_args	*tab;
	t_data	*data;
	char	*line;

	(void)argc;
	(void)argv;
	data = (t_data *)malloc(sizeof(t_data));
	ft_init_struct(tab, data);
	ft_crt_envp(data, env);
	while (1)
	{
		ft_putstr_fd(">>> ", 1);
		get_next_line(0, &line);
		validate_line(line);
		tab = parse_input(line, tab, data);
		free(line);
		line = NULL;
		minishell_start(tab, data);		//команды исполняются до !tab->next
		free_cmd(tab);
		tab = NULL;
	}
	return (0);
}

