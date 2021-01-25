/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 18:16:26 by psemsari          #+#    #+#             */
/*   Updated: 2021/01/20 10:26:17 by bemoreau         ###   ########.fr       */
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
	t_command *tmp;
	t_list *lst_tmp;

	tmp = command;
	while (tmp != NULL)
	{
		printf("COMMAND:\n");
		lst_tmp = tmp->argument;
		while (lst_tmp != NULL)
		{
			printf("	arg: -%s-\n", (char *)lst_tmp->content);
			lst_tmp = lst_tmp->next;
		}
		lst_tmp = tmp->redir_in;
		while (lst_tmp != NULL)
		{
			printf("	redir_in: -%s-\n", (char *)lst_tmp->content);
			lst_tmp = lst_tmp->next;
		}
		lst_tmp = tmp->redir_out;
		while (lst_tmp != NULL)
		{
			printf("	redir_out: -%s-\n", (char *)lst_tmp->content);
			lst_tmp = lst_tmp->next;
		}
		lst_tmp = tmp->redir_append;
		while (lst_tmp != NULL)
		{
			printf("	redir_append: -%s-\n", (char *)lst_tmp->content);
			lst_tmp = lst_tmp->next;
		}
		tmp = tmp->pipe;
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

	str = ft_strdup(str);
	while (*str)
	{
		command = setup_command();
		parser_token(&str, command, env, spipe);
		print_multi_command(command);
		//printf("EXEC\n");
		execution(env, command, redir, spipe);
		clear_multi_command(command);
	}

	return (0);
}
