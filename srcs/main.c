/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 16:29:57 by cjani             #+#    #+#             */
/*   Updated: 2021/01/12 18:19:04 by cquiana          ###   ########.fr       */
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
			ft_putstr_fd("$> ", 0);
		}
		else
			ft_putstr_fd("\n", 1);
		gl_status = 1;
	}
	if (s == SIGQUIT)
	{
		if (read_status)
		{
			ft_putstr_fd("\b\b  \b\b", 1);
		}
		gl_status = 131;
	}
}

// void		ft_read_and_start(t_data *data)
// {
// 	t_args	*tab;
// 	char	*line;
// 	int		ret;

// 	while (1)
// 	{
// 		ft_putstr_fd("\b\b\b$> ", 1);
// 		ret = get_line(0, &line);
// 		if (ret == 42)
// 		{
// 			ft_putendl_fd("Exit minishell", 1);
// 			exit(gl_status);
// 		}
// 		else
// 		{
// 			validate_line(line, data);
// 			tab = parse_input(line, tab, data);
// 			free(line);
// 			line = NULL;
// 			minishell_start(tab, data);		//команды исполняются до !tab->next
// 			free_cmd(tab);
// 			tab = NULL;
// 		}
// 	}
// }

void		handle_ctrl_d(int ret)
{
	if (ret == 42)
	{	ft_putendl_fd("Exit minishell", 1);
		exit(gl_status);
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
	ft_init_struct(data);
	ft_crt_envp(data, env);
	// ft_read_and_start(data);
	while (1)
	{
		ft_putstr_fd("\b\b\b$> ", 1);
		ret = get_line(0, &line);
		handle_ctrl_d(ret);
		// if (ret == 42)
		// {
		// 	ft_putendl_fd("Exit minishell", 1);
		// 	exit(gl_status);
		// }
		// else
		// {
			validate_line(line, data);
			tab = parse_input(line, tab, data);
			free(line);
			line = NULL;
			minishell_start(tab, data);		//команды исполняются до !tab->next
			free_cmd(tab);
			tab = NULL;
		// }
		// ft_putstr_fd("\b\b\b$> ", 1);
	}
	return (0);
}

