#include "minishell.h"

int		list_env(void)
{
	t_var_env *var_env;

	while (g_env != NULL)
	{
		var_env = (t_var_env *)g_env->content;
		ft_putstr_fd(var_env->key, 1);
		ft_putchar_fd('=', 1);
		ft_putendl_fd(var_env->var, 1);
		g_env = g_env->next;
	}
	return (0);
}
