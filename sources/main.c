#include "minishell.h"

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
	char	*str;
	pid_t	child;
	int		ret;
	//int		i = 0;
	//char	**arg;
	// arg = malloc(sizeof(char *) * 4);
	// arg[4] = NULL;
	// while (i < 5)
	// {
	// 	arg[i] = malloc(sizeof(char) * 3);
	// 	arg[i][2] = '\0';
	// 	i++;
	// }
	// arg[0][0] = 'l';
	// arg[0][1] = 's';
	// arg[1][0] = '-';
	// arg[1][1] = 'l';
	// arg[2][0] = '-';
	// arg[2][1] = 'a';
	// arg[3][0] = '.';
	// arg[3][1] = '\0';
	// av[0] = "ls";
	// printf("%d %s\n", execve("/bin/ls", av, envp), strerror(errno));
	while (1)
	{
		ft_putstr("minishell> ");
		get_next_line(0, &str);
		path(envp, str);
	}

	// while (1)
	// {
	// 	ft_putnstr("prompt> ", 9);
	// 	get_next_line(0, &str);
	// 	av[0] = str;
	// 	printf("%d %s\n", execve("/bin/ls", av, envp), strerror(errno));
	// 	free(str);
	// }

	//ajouter var env dans minishell ou mac
	// while (envp[i] != NULL)
	// {
	// 	printf("%s\n", envp[i]);
	// 	i++;
	// }

	// while (1)
	// {
	// 	ft_putnstr("prompt> ", 9);
	// 	get_next_line(0, &str);
	// 	free(str);
	// }

	// printf("%d %d\n", getpid(), child);
	// child = fork();
	// if (child == 0)
	// {
	// 	printf("## child ## %d %d\n", getpid(), child);
	// }
	// else
	// 	printf("## parent ## %d %d\n", getpid(), child);

	// printf("## parent ## %d %d\n", getpid(), child);
	// child = fork();
	// if (child == 0)
	// {
	// 	printf("## child ## %d %d\n", getpid(), child);
	// 	sleep(1);
	// }
	// else
	// {
	// 	waitpid(child, &ret, WUNTRACED);
	// 	printf("## parent ## %d %d\n", getpid(), child);
	// }
	return 0;
}