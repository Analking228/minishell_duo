/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_quote_util.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 19:16:50 by cquiana           #+#    #+#             */
/*   Updated: 2021/01/11 09:53:45 by cquiana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char *ft_crt_res(char *line, int start, int *i, int *flag)
{
    char *res;

    *flag = 0;
    res = ft_substr(line, start, *i - start);
    (*i)++;
    return (res);
}

char	*parse_squote(char *arg, char *line, int *i)
{
    char    *res;
    int     flag;
    int     start;

    flag = 1;
    (*i)++;
    start = *i;
    while (line[(*i)] && flag)
    {
        if (line[(*i)] == '\'')
        {
            res = ft_crt_res(line, start, i, &flag);
			arg = ft_strjoinf(arg, res); //need add  free() in strjoin
			free(res);
            return (arg);
        }
        (*i)++;
    }
    if (flag)
   {
        ft_putstr_fd("error \'\n", 1);
        arg = ft_strdup("");
        return (arg);
    }
	return (NULL);
}

char    *simple_parse(char *arg, char *line, int *i, t_data *data)
{
    char    *envp_value = NULL;

    while (line[(*i)] && (!ft_strchr(" ;><|\'\"", line[(*i)])))
    {
		if (line[(*i)] == '\\')
			(*i)++;
		else if (line[(*i)] == '$')
            envp_value = parse_envp(data, line, i);
        if (envp_value)
            arg = ft_strjoinf(arg, envp_value); // free
        else
            arg = add_symbol(arg, line[(*i)]);
        (*i)++;
    }
    return(arg);
}

static int     check_dq(char c)
{
    return (c == '"');
}

char    *parse_dquote(char *arg, char *line, int *i, t_data *data)
{
    int     flag;

    flag = check_dq(line[++(*i)]);
    while (line[(*i)] && flag == 0)
    {
        if ((flag = check_dq(line[(*i)])))
            break;
		if (line[(*i)] == '\\' && (ft_strchr("$\"\\", line[(*i) + 1])))
        {
			(*i)++;
            arg = add_symbol(arg, line[(*i)++]);
            if ((flag = check_dq(line[(*i)])))
                break;
        }
		if (line[(*i)] == '$')
            arg = ft_strjoinf(arg, parse_envp(data, line, i)); // free
        else
            arg = add_symbol(arg, line[(*i)++]);
    }
    (*i)++;
    if (!flag)
    {
        ft_putstr_fd("error \"\n", 1);
        arg = ft_strdup("");
    }
	return (arg);
}
