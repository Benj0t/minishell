#include "minishell.h"

int		ft_cd(char **env, char *dir)
{
	char *cwd;

	if (chdir(dir) == -1)
		return (-1);
	return (0);
}