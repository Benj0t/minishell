#include "minishell.h"

int		ft_cd(char *dir)
{
	char *cwd;

	getcwd()
	if (chdir(dir) == -1)
		return (-1);
	return (0);
}
