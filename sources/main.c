#include "minishell.h"
#include "pipe.h"
#include "parser.h"

void	ft_putstr(char *str)
{
	int i;

	i = 0;
	while (str[i])
		write(1, &(str[i++]), 1);
}

int main(int ac, char **av, char **envp)
{
	(void)ac;
	char		*str;
	pid_t		child;
	int			ret;
	t_redir		redir;
	t_list		*env;
	s_pipe		spipe;

	env = envp_to_list(envp);
	set_env_var("lol", "hey", env);
	spipe.ret = 0;
	while (1)
	{
		ft_pwd();
		ft_putstr("> ");
		get_next_line(0, &str);
		parser(str, env, &redir, &spipe);
		free(str);
	}
	free(str);
	ft_lstclear(&env, free);
	return 0;
}
