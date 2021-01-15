/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <cquiana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 12:50:21 by cjani             #+#    #+#             */
/*   Updated: 2021/01/09 17:23:24 by cquiana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MINISHELL_H__
# define __MINISHELL_H__

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <limits.h>
# include <signal.h>
# include "../libft/libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/* Внутри структуры есть инт для спец символа */

# define STD 0			/* одна введенная команда */
# define SMCLN 1		/* точка запятая */
# define PIPE 2			/* пайп */
# define RLR 3			/* релинк направо*/
# define RLL 4			/* релинк налево */
# define DRLR 5			/* двойной направо */

/* Важное замечание! Начинаем обработку 1 команды, только после
встречи со спец символом разделения команд. Таким образом будет
очень удобно работать с редиректами */


typedef struct	s_args
{
	char		**cmd;  	/*массив команда + аргументы(в каждом листе списка он свой,
							если подается больше чем 1 команда). НУЛЬТЕРМИНИРОВАННЫЙ!*/
	char		*exec_path;

	int			simbol; 	/*знак, разделяющий команды(пайп, редирект или точка зпт)
							говорит, как использовать вывод нынешней команде
							Отдельно или в зависимости от исполнения предыдущей. См. DEFINE символов*/
	int			simbol_last;/*знак, разделявший предыдущую и нынешнюю команды
							(пайп, редирект или точка зпт) говорит, как действовать
							нынешней команде. Использовать входящие дынные
							Отдельно или в зависимости от исполнения предыдущей.
							См. DEFINE символов*/
	int				fd[2];
	struct s_args	*next;	/* Указатель на следующий лист с командами и последующим
							знакомб если такой есть */
}					t_args;

typedef struct s_data
{
	char		**envp; 	/* указатель на массив окружения(скопированный) */
	char		*oldpwd;	/* необходима для удобного изменения export'а OLDPWD
							в соответствии с изменением рабочих дирикторий */
	char		*curpwd;	/* см. выше. аналогично с PWD */
	int			exec_code;	/* Код выполнения последней команды */
	int			fd_1;		/* вывод наших функций, при пайпах и редиректах изменяется */
	int			fd_0;		/*  ввод (см. выше) */
	int			fd_out;
	int			fd_in;
}				t_data;

typedef struct  s_pars
{
    int         c;
    int         i;
    char        *arg;
    char        **arr;
}               t_pars;

int				read_status;
int				gl_status;

/* shell part */

int				minishell_pwd(char **cmd, t_data *data);
int				minishell_cd(char **cmd, t_data *data);
int				minishell_echo(char **cmd, t_data *data);
int				minishell_export(char **cmd, t_data *data);
int				minishell_export_str_prove(char *str1, char *str2);
int				minishell_exit(t_args *tab, t_data *data);
int				minishell_unset(t_args *tab, t_data *data);
int				minishell_env(char **cmd, t_data *data);
int				minishell_execve(t_args *tab, t_data *data);
int				minishell_start(t_args *tab, t_data *data);
int				minishell_redirect_out(t_args *tab, t_data *data);
int				minishell_redirect_in(t_args *tab, t_data *data);
void			minishell_pipe(t_args *tab, t_data *data);
int				ft_env_srch_len(char *str);
void			ft_init_struct(t_data *data);
t_data			*ft_crt_envp(char **env);
int				ft_envp_count(t_data *data);
void			ft_error(char *str, int fd);
int				ft_envp_srch(char *envp_name, t_data *data);
char			*ft_envp_srch_str(char *envp_name, t_data *data);
int				ft_polygon(t_args *tab, t_data *data, int cmd);

/* parser part */

t_args			*parse_input(char *line, t_args *tab, t_data *data);
char			**double_array_realloc(char **array, int size);
char			*add_symbol(char *str, char c);
void			parse_exec_path(t_data *data, t_args *tab);
int				ft_is_builtin(char *cmd);
int				array_len(char **array);
void			free_cmd(t_args *tab);
void			ft_free_double_array(char **cmd);
t_pars			ft_reset(t_pars  p);
t_pars			ft_init_pars_sruc(void);
void			ft_check_list(t_args *tab);
char			**ft_crt_arr(char **arr, char *str, int *i);
int				ft_skip_space(char *str, int i);
void    		ft_add_back(t_args **lst, t_args *elem);
t_args  		*ft_crt_new(char **array, char *line, int *i, t_data *data);
int				ft_list_len(t_args *tab);
int				array_len(char **array);
char			*parse_envp(t_data *data, char *line, int *i);
void    		ft_set_simbol(t_args *tab, int *save_sym);
char			*parse_squote(char *arg, char *line, int *i);
char    		*parse_dquote(char *arg, char *line, int *i, t_data *data);
char    		*simple_parse(char *arg, char *line, int *i, t_data *data);
void	        validate_line(char *line, t_data *data);
char			*ft_strjoinf(char const *s1, char const *s2);
int				get_line(int fd, char **line);
char			*ft_env_value(char *key, t_data *data);
int				check_double_pipe(char *line);
int				check_double_sem(char *line);
int				is_space(char c);

#endif
