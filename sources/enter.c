/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 18:16:26 by psemsari          #+#    #+#             */
/*   Updated: 2021/01/18 13:44:28 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//desalloc et clear t_command
void		clear_multi_command(t_command *command)
{
	t_command	*tmp;

	tmp = NULL;
	while (command != NULL)
	{
		tmp = command->pipe;
		ft_lstclear(&command->argument, free);
		ft_lstclear(&command->redir_in, free);
		ft_lstclear(&command->redir_append, free);
		ft_lstclear(&command->redir_out, free);
		free(command);
		command = tmp;
	}
}

//print t_command
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

//start du parser
int		parser(char *str, t_list *env, t_redir *redir, s_pipe *spipe)
{
	t_command	*command;
	t_list		*arg;

	str = ft_strdup(str);
	while (str[0] != '\0')
	{
		command = setup_command();
		parser_token(&str, command, env, spipe);
		//print_multi_command(command);
		//printf("EXEC\n");
		execution(env, command, redir, spipe);
		clear_multi_command(command);
	}

	return (0);
}
