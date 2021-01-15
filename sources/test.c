#include "stdio.h"
#include "minishell.h"
#include "token.h"

t_command	*setup_command(void)
{
	t_command	*ret;

	ret = malloc(sizeof(t_command));
	ret->argument = NULL;
	ret->redir_in = NULL;
	ret->redir_out = NULL;
	ret->redir_append = NULL;
	ret->pipe = NULL;
	return (ret);
}

void		print_multi_command(t_command *command)
{
	while (command != NULL)
	{
		printf("COMMAND:\n");
		while (command->argument != NULL)
		{
			printf("	arg: -%s-\n", (char *)command->argument->content);
			command->argument = command->argument->next;
		}
		while (command->redir_in != NULL)
		{
			printf("	redir_in: -%s-\n", (char *)command->redir_in->content);
			command->redir_in = command->redir_in->next;
		}
		while (command->redir_out != NULL)
		{
			printf("	redir_out: -%s-\n", (char *)command->redir_out->content);
			command->redir_out = command->redir_out->next;
		}
		while (command->redir_append != NULL)
		{
			printf("	redir_append: -%s-\n", (char *)command->redir_append->content);
			command->redir_append = command->redir_append->next;
		}
		command = command->pipe;
	}
}

int main(int argc, char const *argv[], char **envp)
{
	char		*str;
	t_token		tok;
	t_list		*env;
	t_command	*command;

	//str = ft_strdup("cat <lol.c>> out;echo $yop \"$yop\" '$yop'");
	// while (str)
	// {
	// 	tok = next_token(&str);
	// 	printf("-%s- %d\n", tok.name, (int)tok.type);
	// }
	env = envp_to_list(envp);
	str = ft_strdup("cat <lol.c>> out | grep hey");
	str = ft_strdup("echo $yop \"$yop hey\" '$yop'");
	//str = ft_strdup(argv[1]);
	command = setup_command();
	parser_token(&str, command, env);
	print_multi_command(command);
	return 0;
}

//cat <lol.c>> out;echo $yop \"$yop\" '$yop'
//separator =
