/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 21:40:07 by cquiana           #+#    #+#             */
/*   Updated: 2021/01/08 18:12:08 by cquiana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char    *parse_envp(t_data *data, char *line, int *i)
{
    char    *key;
    char    *res;
    int     j;

    (*i)++;
    j = 0;
    if (line[(*i)] == ' ' || line[(*i)] == '\0' || line[(*i)] == '"')
        return(res = ft_strdup("$"));
    if (line[(*i)] == '?')
        return(res = ft_itoa(data->exec_code));
    key = ft_strdup("");
    res = ft_strdup("");
    while (line[(*i)] && line[(*i)] != ' ' && line[(*i)] != '"')
        key = add_symbol(key, line[(*i)++]);
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

int     check_dq(char c)
{
    return (c == '"');
}

static char    *parse_dquote(char *arg, char *line, int *i, t_data *data)
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
            arg = ft_strjoin(arg, parse_envp(data, line, i)); // free
        else
            arg = add_symbol(arg, line[(*i)++]);
    }
    (*i)++;
    if (!flag)
    {
        printf("error \"\n");
        arg = ft_strdup("");
    }
	return (arg);
}

// static char    *parse_dquote(char *arg, char *line, int *i, t_data *data)
// {
//     char    *envp_value;
//     int     flag;

//     flag = 0;
//     (*i)++;
//     envp_value = NULL;
//     while (line[(*i)] && !flag)
//     {
//         if (line[(*i)] == '\"')
//         {
//             flag = 1;
//             break;
//         }
// 		if (line[(*i)] == '\\' && (ft_strchr("$\"\\", line[(*i) + 1])))
//         {
// 			(*i)++;
//             arg = add_symbol(arg, line[(*i)++]);
//             if (line[(*i)] == '\"')
//             {
//                 flag = 1;
//                 break;
//             }
//         }
// 		else if (line[(*i)] == '$')
//             arg = ft_strjoin(arg, parse_envp(data, line, i));
//         else
//             arg = add_symbol(arg, line[(*i)]);
//         (*i)++;
//     }
//     (*i)++;
//     if (!flag)
//     {
//         printf("error \"\n");
//         arg = ft_strdup("");
//     }
// 	return (arg);
// }


static char *ft_crt_res(char *line, int start, int *i, int *flag)
{
    char *res;

    *flag = 0;
    res = ft_substr(line, start, *i - start);
    (*i)++;
    return (res);
}

static char *parse_squote(char *arg, char *line, int *i)
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
			arg = ft_strjoin(arg, res); //need add  free() in strjoin
			free(res);
            return (arg);
        }
        (*i)++;
    }
    if (flag)
   {
        printf("error \'\n");
        arg = ft_strdup("");
        return (arg);
    }
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

void    ft_add_back(t_args **lst, t_args *elem)
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

t_args    *ft_init_arg(t_args *new, char **arr)
{
    int j;

    j = 0;
    new = (t_args *)malloc(sizeof(t_args)); // error malloc
    new->cmd = NULL;
    new->cmd = (char **)malloc(sizeof(char*) * (array_len(arr) + 1)); // error
    while (arr[j] != NULL)
    {
        new->cmd[j] = ft_strdup(arr[j]);
        j++;
    }
    new->cmd[j] = NULL;
    new->exec_path = NULL;
    return (new);
}

t_args  *ft_crt_new(char **array, char *line, int *i, t_data *data)
{
    t_args  *new;

    if (!array || line[(*i) + 1] == ';')
        return (NULL);
    new = ft_init_arg(new, array);
	new->simbol = cmd_parse(line, i);
    if ((ft_is_builtin(new->cmd[0])) == 0)
        new->exec_path = NULL;
    else if (!(ft_strchr("./", new->cmd[0][0])))
        parse_exec_path(data, new);
    else
        new->exec_path = ft_strdup(new->cmd[0]);
	new->next = NULL;
    ft_free_double_array(array);
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

char    **ft_crt_arr(char **arr, char *str, int *i)
{

    arr = double_array_realloc(arr, 1);
    arr[(*i)] = ft_strdup(str);
    (*i)++;
    free(str);
    str = NULL;
    return (arr);
}

t_pars    ft_init_pars_sruc(void)
{
    t_pars p;

    p.i = 0;
    p.c = 0;
    p.arg = NULL;
    p.arr = NULL;
    return (p);
}

int    ft_skip_space(char *str, int i)
{
    while (str[i] == ' ')
        i++;
    return (i);
}

char    *parse_line(char *arg, char *line, int *i, t_data *data)
{
    if (line[(*i)] && line[(*i)] == '\'')
        arg = parse_squote(arg, line, i);
	else if (line[(*i)] && line[(*i)] == '\"')
        arg = parse_dquote(arg, line, i, data);
    else if (!ft_strchr(" ;><|", line[(*i)]))
        arg = simple_parse(arg, line, i, data);
    return (arg);
}

t_pars     ft_reset(t_pars  p)
{
    p.i++;
    p.c = 0;
    p.arr = NULL;
    return (p);
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
