/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 21:40:07 by cquiana           #+#    #+#             */
/*   Updated: 2021/01/17 22:10:11 by cquiana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*dollar_cases(t_data *data, char *line, int *i)
{
	char	*res;

	if (line[(*i)] == ' ' || line[(*i)] == '\0' || line[(*i)] == '"')
		return (res = ft_strdup("$"));
	if (line[(*i)] == '?')
		return (res = ft_itoa(g_status));
	if (ft_strchr("0123456789", line[(*i)]))
		(*i)++;
	return (NULL);
}

static char	*ft_get_key(char *line, int *i, char *key)
{
	while (line[(*i)] && line[(*i)] != ' ' &&
		line[(*i)] != '"' && line[(*i)] != '$')
	{
		key = add_symbol(key, line[(*i)++]);
		if (line[(*i)] == '$')
		{
			(*i)++;
			free(key);
			key = NULL;
			if (!(key = ft_strdup("")))
				ft_error("malloc error\n", 2);
			while (line[(*i)] && line[(*i)] != ' ' && line[(*i)] != '"')
				key = add_symbol(key, line[(*i)++]);
			return (key);
		}
	}
	return (key);
}

char		*parse_envp(t_data *data, char *line, int *i)
{
	char	*key;
	char	*res;

	(*i)++;
	if (ft_strchr("0123456789 \"?\0", line[(*i)]))
	{
		res = dollar_cases(data, line, i);
		return (res);
	}
	if (!(key = ft_strdup("")))
		ft_error("malloc error\n", 2);
	key = ft_get_key(line, i, key);
	key = add_symbol(key, '=');
	res = ft_env_value(key, data);
	free(key);
	key = NULL;
	return (res);
}

static char	*parse_line(char *arg, char *line, int *i, t_data *data)
{
	if (line[(*i)] && line[(*i)] == '\'')
		arg = parse_squote(arg, line, i);
	else if (line[(*i)] && line[(*i)] == '\"')
		arg = parse_dquote(arg, line, i, data);
	else if (!ft_strchr(" ;><|", line[(*i)]))
		arg = simple_parse(arg, line, i, data);
	return (arg);
}

t_args		*parse_input(char *line, t_data *data)
{
	t_pars	p;
	t_args	*new;

	new = NULL;
	p = ft_init_pars_sruc();
	while (line[p.i])
	{
		p.i = ft_skip_space(line, p.i);
		if (!(p.arg = ft_calloc(sizeof(char), 1)))
			ft_error("malloc error\n", 2);
		while (line[p.i] && line[p.i] != ' ')
		{
			if (ft_strchr(";><|", line[p.i]))
			{
				ft_add_back(&new, ft_crt_new(p.arr, line, &p.i, data));
				p = ft_reset(p);
				break ;
			}
			p.arg = parse_line(p.arg, line, &p.i, data);
			if ((ft_strchr(" ;><|", line[p.i]) || !line[p.i]))
				p.arr = ft_crt_arr(p.arr, p.arg, &(p.c));
		}
	}
	ft_add_back(&new, ft_crt_new(p.arr, line, &p.i, data));
	ft_check_list(new);
	ft_free_pars_sruc(p);
	return (new);
}
