/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <cquiana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 21:40:07 by cquiana           #+#    #+#             */
/*   Updated: 2021/01/09 18:16:46 by cquiana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char *dollar_cases(t_data *data, char *line, int *i)
{
    char    *res;

    if (line[(*i)] == ' ' || line[(*i)] == '\0' || line[(*i)] == '"')
        return(res = ft_strdup("$"));
    if (line[(*i)] == '?')
        return(res = ft_itoa(data->exec_code));
    if (ft_strchr("0123456789", line[(*i)]))
        (*i)++;
    return (NULL);
}

static char *ft_get_key(char *line, int *i, char *key)
{
    while (line[(*i)] && line[(*i)] != ' ' && line[(*i)] != '"' && line[(*i)] != '$')
    {
        key = add_symbol(key, line[(*i)++]);
        if (line[(*i)] == '$')
        {
           (*i)++;
            free(key);
            key = NULL;
            key = ft_strdup("");
            while (line[(*i)] && line[(*i)] != ' ' && line[(*i)] != '"')
                key = add_symbol(key, line[(*i)++]);
            return (key);
        }
    }
    return (key);
}

char        *parse_envp(t_data *data, char *line, int *i)
{
    char    *key;
    char    *res;
    int     j;

    (*i)++;
    j = 0;
    if (ft_strchr("0123456789 \"?\0", line[(*i)]))
        return (res = dollar_cases(data, line, i));
    key = ft_strdup("");
    res = ft_strdup("");
    key = ft_get_key(line, i, key);
    key = add_symbol(key, '=');
    while (data->envp[j])
    {
        if (ft_strncmp(key, data->envp[j], ft_strlen(key)) == 0)
            res = ft_strjoin(res, data->envp[j] + ft_strlen(key));
        j++;
    }
    free(key);
    key = NULL;
    return (res);
}

static char *parse_line(char *arg, char *line, int *i, t_data *data)
{
    if (line[(*i)] && line[(*i)] == '\'')
        arg = parse_squote(arg, line, i);
	else if (line[(*i)] && line[(*i)] == '\"')
        arg = parse_dquote(arg, line, i, data);
    else if (!ft_strchr(" ;><|", line[(*i)]))
        arg = simple_parse(arg, line, i, data);
    return (arg);
}

t_args    *parse_input(char *line, t_args *tab, t_data *data)
{
    t_pars  p;

    p = ft_init_pars_sruc();
    while (line[p.i])
    {
        p.i = ft_skip_space(line, p.i);
        p.arg = ft_strdup("");
        while (line[p.i] && line[p.i] != ' ')
        {
            if (ft_strchr(";><|", line[p.i]))
            {
                ft_add_back(&tab, ft_crt_new(p.arr, line, &p.i, data));
                p = ft_reset(p);
                break ;
            }
            p.arg = parse_line(p.arg, line, &p.i, data);
            if (ft_strncmp(p.arg, "", 1) != 0 &&
                (ft_strchr(" ;><|", line[p.i]) || !line[p.i]))
                p.arr = ft_crt_arr(p.arr, p.arg, &(p.c));
        }
    }
    ft_add_back(&tab, ft_crt_new(p.arr, line, &p.i, data));
    ft_check_list(tab);
    p = ft_init_pars_sruc(); // null
    return (tab);
}
