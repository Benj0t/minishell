#include "minishell.h"
#include "pipe.h"
#include "parser.h"

pid_t	child;
int		sig_ret;

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
		sig_ret = 130;
		kill(child, SIGTERM);
	}
	return ;
}

int main(int ac, char **av, char **envp)
{
	(void)ac;
	char		*str;
	t_redir		redir;
	t_list		*env;
	s_pipe		spipe;
	int			pid;

	pid = 0;
	spipe.last_ret = 0;
	sig_ret = 0;
	env = envp_to_list(envp);
	set_env_var("lol", "hey", env); //test
	spipe.ret = 0;
	child = 0;
	while (1)
	{
		sig_ret = 0;
		ft_putstr_fd("> ", 2);
		signal(SIGQUIT, &sig_handler);
		signal(SIGINT, &sig_handler);
		//child = fork();
		if (child == 0)
		{
			gnl_prompt(0, &str);
			parser(str, env, &redir, &spipe);
			free(str);
			exit(spipe.last_ret);
		}
		//waitpid(child, &pid, 0);
		spipe.last_ret = WEXITSTATUS(pid);
		if (sig_ret)
			spipe.last_ret = sig_ret;
		if (spipe.last_ret == 9)
			exit(9);
	}
	free(str);
	ft_lstclear(&env, free);
	return 0;
}
