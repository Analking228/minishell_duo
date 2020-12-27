/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 21:40:07 by cquiana           #+#    #+#             */
/*   Updated: 2020/12/27 20:26:38 by cquiana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char    *parse_envp(t_data *data, char *line, int *i)
{
    char    *key;
    char    *res;
    int     len;
    int     j;

    (*i)++;
    len = 0;
    j = 0;
    // add $?
    key = ft_strdup("");
    res = ft_strdup("");
    while (line[(*i)] && line[(*i)] != ' ' && line[(*i)] != '"')
    {
        key = add_symbol(key, line[(*i)]);
        (*i)++;
        len++;
    }
    (*i)--;
    while (data->envp[j])
    {
        if (ft_strncmp(key, data->envp[j], len) == 0)
            res = ft_strjoin(res, data->envp[j] + (++len));
        j++;
    }
    return (res);
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
        if (envp_value) //
            arg = ft_strjoin(arg, envp_value);
        else
            arg = add_symbol(arg, line[(*i)]);
        (*i)++;
    }
    return(arg);
}

static char    *parse_dquote(char *arg, char *line, int *i, t_data *data)
{
    char    *envp_value; // for envp
    int     flag;

    flag = 1;
    (*i)++;
    envp_value = NULL;
    while (line[(*i)] && flag)
    {
        if (line[(*i)] == '\"')
        {
            flag = 0;
            break;
        }
		if (line[(*i)] == '\\' && (line[(*i) + 1] == '$' || line[(*i) + 1] == '"' || line[(*i) + 1] == '\\'))
			(*i)++;
		else if (line[(*i)] == '$')
            envp_value = parse_envp(data, line, i);
        if (envp_value)
        {
            arg = ft_strjoin(arg, envp_value);
            envp_value = NULL;
        }
        else
            arg = add_symbol(arg, line[(*i)]);
        (*i)++;
    }
    (*i)++;
    if (flag)
        printf("error \"\n");
	return (arg);
}

static char    *parse_squote(char *arg, char *line, int *i)
{
    char    *res;
    int     flag;
    int     start;
    int     end;

    flag = 1;
    (*i)++;
    start = *i;
    while (line[(*i)] && flag)
    {
        if (line[(*i)] == '\'')
        {
            flag = 0;
            end = *i;
            res = ft_substr(line, start, end - start);
			arg = ft_strjoin(arg, res); //need add  free() in strjoin
			free(res);
            (*i)++;
            return (arg);
        }
        (*i)++;
    }
    if (flag)
        printf("error \'\n");
	return (NULL);
}

int    cmd_parse(char *line, int *i)
{
    if (line[(*i)] == ';')
        return(1);
    else if (line[(*i)] == '|')
        return(2);
    else if (line[(*i)] == '>' && line[(*i) + 1] != '>')
        return(3);
    else if (line[(*i)] == '<')
        return(4);
    else if (line[(*i)] == '>' && line[(*i) + 1] == '>')
        return(5);
    else
        return(0);
    // (*i)++;
}

void    ft_add_back_elem(t_args **lst, t_args *elem)
{
    t_args      *tmp;
    if(!(*lst))
        *lst = elem;
    else
    {
        tmp = *lst;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = elem;
    }
}

int     array_len(char **array)
{
    int     i;

    i = 0;
    while (array[i])
        i++;
    return (i);
}

t_args  *ft_crt_newelem(char **array, char *line, int *i, t_data *data)
{
    t_args  *new;
    int     j;
    int     len;
    j = 0;
    new = (t_args *)malloc(sizeof(t_args)); // error malloc
    new->cmd = NULL;
    while (array[j] != NULL)
    {
        new->cmd = double_array_realloc(new->cmd, 1);
        new->cmd[j] = ft_strdup(array[j]);  ////free array
        // free(array[j]);
        j++;
    }
    // new->cmd[j] = NULL;
    if ((ft_is_builtin(new->cmd[0])) == 0)
        new->exec_path = NULL;
    else if (!(ft_strchr("./", new->cmd[0][0])))
        parse_exec_path(data, new);
    else
        new->exec_path = ft_strdup(new->cmd[0]);
    // printf("path = %s\n", new->exec_path);
	new->simbol = cmd_parse(line, i);
	new->next = NULL;
    // free(array);
    return(new);
}

t_args    *parse_input(char *line, t_args *tab, t_data *data)
{
    int     i;
	int		count;
    char    *arg;
    char    **array;

    i = 0;
    count = 0;
    array = NULL;
    while (line[i])
    {
        arg = ft_strdup("");
        while (line[i] == ' ')
            i++;
        while (line[i] && line[i] != ' ')
        {
            if (ft_strchr(";><|", line[i]))
            {
                count = 0;
                ft_add_back_elem(&tab, ft_crt_newelem(array, line, &i, data));
                i++;
                break;
            }
            if (line[i] && line[i] == '\'')
                arg = parse_squote(arg, line, &i);
			else if (line[i] && line[i] == '\"')
                arg = parse_dquote(arg, line, &i, data);
            else if (!ft_strchr(" ;><|", line[i]))
                arg = simple_parse(arg, line, &i, data);
            // else
        }
        if (ft_strncmp(arg, "", 1) != 0)
        {
            array = double_array_realloc(array, 1);
            array[count++] = ft_strdup(arg);
            free(arg);
            // arg = NULL;
        }
    }
    ft_add_back_elem(&tab, ft_crt_newelem(array, line, &i, data));
    // if ()
        // tab = ft_crt_newelem(array, line, &i, data);
    // printf("cmd = %s\n", tab->cmd[0]);
    return(tab);
}
