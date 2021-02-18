#include "minishell.h"

int		list_env(t_list *env)
{
	t_var_env *var_env;

	while (env != NULL)
	{
		var_env = (t_var_env *)env->content;
		ft_putstr_fd(var_env->key, 2);
		ft_putchar_fd('=', 1);
		ft_putendl_fd(var_env->var, 2);
		env = env->next;
	}
	return (0);
}
