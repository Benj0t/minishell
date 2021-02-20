#include "minishell.h"

int		ft_env(void)
{
	print_env("", g_env, 0);
	return (0);
}
