/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 16:29:57 by cjani             #+#    #+#             */
/*   Updated: 2021/01/11 22:02:53 by cquiana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

	/* Общее начало. Часть закомменченная - начало твоей парсерной части.
	Здесь нужно будет постоянно считывать вводимые данные и парсить их,
	чтобы в дальнейшем я мог ими воспользоваться. Указал в неплохом виде,
	будут какие-то изменения - обязательно оставляй коммент. Название
	твоих файлов и функций прошу начинать с "parser_"					*/


void		signal_handler(int s)
{
	if (s == SIGINT)
	{
		if (read_status)
		{
			ft_putstr_fd("\b\b  \b\b\n", 1);
			ft_putstr_fd("minishell $> ", 1);
		}
		else
			ft_putstr_fd("\n", 1);
			// status
	}
	if (s == SIGQUIT)
	{
		if (read_status)
		{
			ft_putstr_fd("\b\b  \b\b", 1);
			// ft_putstr_fd("Quit: 3\n", 1);
		}
	//status
	}
}


int			main(int argc, char **argv, char **env)
{
	t_args	*tab;
	t_data	*data;
	char	*line;
	int		ret;

	(void)argc;
	(void)argv;
	signal(SIGQUIT, (void *)signal_handler);
	signal(SIGINT, (void *)signal_handler);
	data = (t_data *)malloc(sizeof(t_data));
	ft_init_struct(tab, data);
	ft_crt_envp(data, env);
	while (1)
	{
		ft_putstr_fd("minishell $> ", 1);
		ret = get_line(0, &line);
		if (ret == 42)
		{
			ft_putendl_fd("Exit minishell", 1);
			exit(data->exec_code);
		}
		else
		{
			validate_line(line, data);
			tab = parse_input(line, tab, data);
			free(line);
			line = NULL;
			minishell_start(tab, data);		//команды исполняются до !tab->next
			free_cmd(tab);
			tab = NULL;
		}
	}
	return (0);
}

