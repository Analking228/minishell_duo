/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 16:29:57 by cjani             #+#    #+#             */
/*   Updated: 2020/12/27 18:38:42 by cquiana          ###   ########.fr       */
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
	int		i;
	char	*line;
	char	**tmp;

	(void)argc;
	(void)argv;
	i = 2;
	data = (t_data *)malloc(sizeof(t_data));
	ft_init_struct(tab, data);
	ft_crt_envp(data, env);
	while (1)
	{
		get_next_line(0, &line);
		tab = parse_input(line, tab, data);
		// parse_input(line, tab, data);	//обработка приходящих команд, формирование листа,
										//при необходимости.
		while (tab)
		{
			printf("%s\n", tab->cmd[0]);
			tab = tab->next;
		}
		free(line);
		line = NULL;
		//minishell_start(tab, data);		//команды исполняются до !tab->next
		//free_cmd(tab->cmd, tab->next);
	}
	return (0);
}
