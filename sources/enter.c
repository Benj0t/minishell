/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 18:16:26 by psemsari          #+#    #+#             */
/*   Updated: 2021/02/21 21:24:30 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_pipe(t_command *command)
{
	t_command	*tmp;

	tmp = command->pipe;
	while (tmp != NULL)
	{
		if (tmp->argument == NULL && tmp->redir_in == NULL\
			&& tmp->redir_out == NULL && tmp->redir_append == NULL)
			return (1);
		tmp = tmp->pipe;
	}
	return (0);
}

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
	if (ret == NULL)
		return (NULL);
	ret->argument = NULL;
	ret->redir_in = NULL;
	ret->redir_out = NULL;
	ret->redir_append = NULL;
	ret->pipe = NULL;
	return (ret);
}

//start du parser
int		parser(char **str, t_redir *redir, s_pipe *spipe)
{
	t_managparse	manag;
	t_command		*base;

	manag.str = *str;
	manag.spipe = *spipe;
	while (*manag.str)
	{
		manag.command = setup_command();
		base = manag.command;
		if (parser_token(&manag))
		{
			manag.command = base;
			clear_multi_command(manag.command);
			*str = manag.str;
			return (1);
		}
		manag.command = base;
		if (check_pipe(manag.command))
		{
			clear_multi_command(manag.command);
			return (error_parser(NULL, ft_strdup("parse error near '|'")));
		}
		//debug
		print_multi_command(manag.command);
		printf("exec\n");
		execution(manag.command, redir, spipe);
		clear_multi_command(manag.command);
	}
	*str = manag.str;
	return (0);
}
