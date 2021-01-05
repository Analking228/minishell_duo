/*without any options*/
#include "../includes/minishell.h"

int			minishell_pwd(t_args *tab, t_data *data)
{    
	char	PathName[PATH_MAX];
	char	*pn;
	int	close_out;

	close_out = minishell_redirect_out(tab, data);
	if (!(pn = getwd(PathName)))
		ft_error("getwd error", data->fd_out);
	else
	{
		ft_putstr_fd(PathName, data->fd_out);
		ft_putstr_fd("\n", data->fd_out);
	}
	if (close_out)
	{
		dup2(data->fd_1, 1);
		close(data->fd_1);
	}
	return 0;
}

