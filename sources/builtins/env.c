#include "minishell.h"

static int	env(char **env)
{
	int i;

	i = 0;
	while (env[i])
		ft_putendl_fd(env[i++], 1);
}