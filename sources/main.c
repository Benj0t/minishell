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
	int i;

	i = 3;
	write(1, &i, 1);
	kill(child, 1);
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
	while (1)
	{
		ret = 0;
		signal(SIGINT, &sig_handler);
		ft_pwd();
		ft_putstr("> ");
		child = fork();
		if (child == 0)
		{
			ft_putstr("Je suis le fork");
			get_next_line(0, &str);
			parser(str, env, &redir, &spipe);
			free(str);
			exit(EXIT_SUCCESS);
		}
		waitpid(child, &ret, 0);
	}
	free(str);
	ft_lstclear(&env, free);
	return 0;
}
