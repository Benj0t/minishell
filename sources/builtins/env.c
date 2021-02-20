#include "minishell.h"

int		list_env(void)
{
	print_env(NULL, g_env);
	return (0);
}
