#include "minishell.h"

int		list_env(t_list *env)
{
	t_var_env *var_env;

	while (env != NULL)
	{
		var_env = (t_var_env *)env->content;
		printf("%s=%s\n", var_env->key, var_env->var);
		env = env->next;
	}
	return (0);
}
