#include "minishell.h"

int		ft_cd(char **arg, t_list *env)
{
	char	*pwd;
	char	*home;
	char	**action;

	if (arg[2] != NULL)
		return ();//error too args
	home = get_env_var("HOME", env);
	pwd = getcwd(pwd, 4096);
	action = ft_split(arg[1], '/');
	if (chdir(dir) == -1)
		return (-1);
	return (0);
} // cd HOME path : cd ~ different path
