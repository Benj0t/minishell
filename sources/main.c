#include "minishell.h"
#include "pipe.h"
#include "parser.h"

pid_t	child;
int		sig_ret;
t_list		*env;

void	ft_putstr(char *str)
{
	int i;

	i = 0;
	while (str[i])
		write(1, &(str[i++]), 1);
}

void	sig_handler(int sigid)
{
	if (sigid == SIGINT)
	{
		sig_ret = 130;
		ft_putstr_fd("\n> ", 2);
		close(STDIN_FILENO);
		dup(STDOUT_FILENO);
	}
	return ;
}

int main(int ac, char **av, char **envp)
{
	(void)ac;
	char		*str;
	t_redir		redir;
	s_pipe		spipe;
	int			pid;

	pid = 0;
	spipe.last_ret = 0;
	sig_ret = 0;
	env = envp_to_list(envp);
	set_env_var("lol", "hey", env);
	spipe.ret = 0;
	//child = 0;
	signal(SIGQUIT, &sig_handler);
	signal(SIGINT, &sig_handler);
	while (1)
	{
		ft_putstr_fd("> ", 2);
		sig_ret = 0;
		//child = fork();
		// if (child == 0)
		// {
		gnl_prompt(0, &str);
		parser(&str, &redir, &spipe);
		//printf("%p\n", str);
		free(str);
		// }
		//waitpid(child, &pid, 0);
		//spipe.last_ret = WEXITSTATUS(pid);
		// if (sig_ret)
		// 	spipe.last_ret = sig_ret;
		if (spipe.last_ret == 9)
			exit(9);
	}
	free(str);
	ft_lstclear(&env, free);
	return 0;
}
