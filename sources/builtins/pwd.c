#include "minishell.h"

static int	find_pwd(char **env)
{
	int i;

	i = -1;
	while (env[++i])
		if (env[i][0] == 'P' && env[i][1] == 'W' && env[i][2] == 'D' && env[i][3] == '=')
			return (i);
	return (-1);
}

int		ft_pwd(char **env)
{
	int i;
	char *str;

	printf("AAAAAAAAAAAAAAAA\n");
	if ((i = find_pwd(env)) == -1)
		return (-1);
	str = env[i];
	//ft_putendl_fd(str + 4, 1);
	str = getcwd(str, 4096);
	ft_putendl_fd(str + 4, 1);
	return (0);
}