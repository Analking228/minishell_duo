/*without any options*/
#include "../includes/minishell.h"

int			minishell_pwd(char **cmd, t_data *data)
{
	char	PathName[PATH_MAX];
	char	*pn;

	if (!(pn = getwd(PathName)))
	{
		gl_status = 127;
		ft_error("getwd error", data->fd_out);
	}
	else
	{
		ft_putstr_fd(PathName, data->fd_out);
		ft_putstr_fd("\n", data->fd_out);
	}
	return 0;
}

