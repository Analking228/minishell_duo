/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 21:40:07 by cquiana           #+#    #+#             */
/*   Updated: 2021/01/06 15:33:31 by cquiana          ###   ########.fr       */
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
    if (line[(*i)] == '?')
        return(res = ft_itoa(data->exec_code));
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
        if (envp_value)
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
		if (line[(*i)] == '\\' && !(ft_strchr("$\"\\", line[(*i) + 1])))
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
    if (line[(*i)] == '|')
        return(2);
    else if (line[(*i)] == '>' && line[(*i) + 1] != '>')
        return(3);
    else if (line[(*i)] == '<')
        return(4);
    else if (line[(*i)] == '>' && line[(*i) + 1] == '>')
    {
        (*i)++;
        return(5);
    }
    else
        return(1);
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
    if (!array)
        return (NULL);
    new = (t_args *)malloc(sizeof(t_args)); // error malloc
    new->cmd = NULL;
	new->simbol = cmd_parse(line, i);
    while (array[j] != NULL)
    {
        new->cmd = double_array_realloc(new->cmd, 1);
        new->cmd[j] = ft_strdup(array[j]);
        j++;
    }
    new->exec_path = NULL;
    if ((ft_is_builtin(new->cmd[0])) == 0)
        new->exec_path = NULL;
    else if (!(ft_strchr("./", new->cmd[0][0])))
        parse_exec_path(data, new);
    else
        new->exec_path = ft_strdup(new->cmd[0]);
	new->next = NULL;
    ft_free_double_array(array);
    array = NULL;
    return(new);
}

int     ft_list_len(t_args *tab)
{
    int     len;
    t_args  *tmp;

    len = 0;
    tmp = tab;
    while (tmp)
    {
        tmp = tmp->next;
        len++;
    }
    return (len);
}

void    ft_set_simbol(t_args *tab, int *save_sym)
{
    int     i;
    t_args  *tmp;

    tab->simbol_last = 0;
    tmp = tab->next;
    i = 0;
    while (tmp)
    {
        tmp->simbol_last = save_sym[i];
        tmp = tmp->next;
        i++;
    }
}

void    ft_check_list(t_args *tab)
{
    int     *save_sym;
    int     i;
    t_args  *tmp;

    if (!tab)
        return ;
    i = 0;
    if (tab->next == NULL)
        tab->simbol = 0;
    else
    {
        tab->simbol_last = 0;
        tmp = tab;
        save_sym = (int *)malloc(sizeof(int) * ft_list_len(tab)); // error malloc
        while (tmp)
        {
            save_sym[i] = tmp->simbol;
            tmp = tmp->next;
            i++;
        }
        ft_set_simbol(tab, save_sym);
        free(save_sym);
    }
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
        while (line[i] == ' ')
            i++;
        arg = NULL;
        arg = ft_strdup("");
        while (line[i] && line[i] != ' ')
        {
            if (line[i] && line[i] == '\'')
                arg = parse_squote(arg, line, &i);
			else if (line[i] && line[i] == '\"')
                arg = parse_dquote(arg, line, &i, data);
            else if (!ft_strchr(" ;><|", line[i]))
                arg = simple_parse(arg, line, &i, data);
            // else
            if (ft_strchr(";><|", line[i]) && line[i])
            {
                count = 0;
                ft_add_back_elem(&tab, ft_crt_newelem(array, line, &i, data));
                i++;
                array = NULL;
                break;
            }
        }
        if (ft_strncmp(arg, "", 1) != 0)
        {
            array = double_array_realloc(array, 1);
            array[count++] = ft_strdup(arg);
            free(arg);
        }
    }
    ft_add_back_elem(&tab, ft_crt_newelem(array, line, &i, data));
    array = NULL;
    ft_check_list(tab);
    return(tab);
}
