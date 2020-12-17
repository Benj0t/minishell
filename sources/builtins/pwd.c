#include "minishell.h"

int		ft_pwd(t_list **env)
{
	char	*str;

	str = get_env_var("PWD", env);
	if (str == NULL)
		return (-1);
	else
		ft_putstr_fd(str, 1);
	return (0);
}
