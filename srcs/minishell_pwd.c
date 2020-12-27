/*without any options*/
#include "../includes/minishell.h"

int			minishell_pwd(t_data *data, int fd_out)
{    
	char	PathName[PATH_MAX];
	char	*pn;

	if (!(pn = getwd(PathName)))
		ft_error("getwd error", data->fd_1);
	else
	{
		ft_putstr_fd(PathName, data->fd_1);
		ft_putstr_fd("\n", data->fd_1);
	}
	return 0;
}

