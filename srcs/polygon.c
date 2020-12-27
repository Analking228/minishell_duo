#include "../includes/minishell.h"

static int	free_tmp(char **tmp, int count)
{
	while (count)
	{
		free(tmp[count]);
		count--;
	}
	free(tmp[count]);
	free(tmp);
	tmp = NULL;
	return (1);
}

int		ft_polygon(t_args *tab, t_data *data, int cmd)
{
	minishell_start(tab, data);
	//minishell_export(tab, data);
	free_tmp(tab->cmd, cmd);
	tab->cmd = (char **)malloc(sizeof(char *) * 2);
	tab->cmd[0] = ft_strdup("export");
	tab->cmd[1] = NULL;
	minishell_start(tab, data);
	//minishell_export(tab, data);
	free_tmp(tab->cmd, 1);
	tab->cmd = (char **)malloc(sizeof(char *) * 4);
	tab->cmd[0] = ft_strdup("unset");
	tab->cmd[1] = ft_strdup("PWD");
	tab->cmd[2] = ft_strdup("AMD");;
	tab->cmd[3] = NULL;
	minishell_start(tab, data);
	//minishell_unset(tab, data);
	free_tmp(tab->cmd, 2);
	tab->cmd = (char **)malloc(sizeof(char *) * 2);
	tab->cmd[0] = ft_strdup("export");
	tab->cmd[1] = NULL;
	minishell_start(tab, data);
	//minishell_export(tab, data);
	return (1);
}