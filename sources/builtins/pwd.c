#include "minishell.h"
#include "limits.h"

int		ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(pwd, 4096);
	if (pwd == NULL)
		return (-1);
	else
		ft_putstr_fd(pwd, 1);
	return (0);
}
