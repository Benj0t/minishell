#include "minishell.h"
#include "limits.h"

int		ft_pwd(void)
{
	char	*pwd;

	pwd = getenv("PWD");
	if (pwd == NULL)
		return (-1);
	else
		ft_putstr_fd(pwd, 2);
	ft_putchar_fd('\n', 2);
	return (0);
}
