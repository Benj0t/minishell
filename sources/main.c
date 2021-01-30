#include "minishell.h"
#include "pipe.h"
#include "parser.h"

pid_t child;

void	ft_putstr(char *str)
{
	int i;

	i = 0;
	while (str[i])
		write(1, &(str[i++]), 1);
}

void	sig_handler(int sigid)
{
	if (sigid == SIGINT && child != 0)
	{
		write(1, "\n", 1);
		kill(child, SIGTERM);
	}
	return ;
}

int main(int ac, char **av, char **envp)
{
	(void)ac;
	char		*str;
	int			ret;
	t_redir		redir;
	t_list		*env;
	s_pipe		spipe;

	spipe.last_ret = 0;
	env = envp_to_list(envp);
	set_env_var("lol", "hey", env); 
	spipe.ret = 0;
	child = 0;
	while (1)
	{
		ft_pwd();
		ft_putstr("> ");
		signal(SIGQUIT, &sig_handler);
		signal(SIGINT, &sig_handler);
		child = fork();
		if (child == 0)
		{
			get_next_line(0, &str);
			parser(str, env, &redir, &spipe);
			free(str);
			kill(getpid(), SIGTERM);
		}
		waitpid(child, &ret, 0);
	}
	free(str);
	ft_lstclear(&env, free);
	return 0;
}
