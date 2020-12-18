#include "minishell.h"
#include "limits.h"

int		ft_pwd(void)
{
	char	*str;

	getcwd(str, PATH_MAX)

	str = get_env_var("PWD", env);
	if (str == NULL)
		return (-1);
	else
		ft_putstr_fd(str, 1);
	return (0);
}
