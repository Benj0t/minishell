/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 18:16:26 by psemsari          #+#    #+#             */
/*   Updated: 2021/02/26 20:43:50 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			check_pipe(t_command *command)
{
	t_command	*tmp;

	tmp = command->pipe;
	while (tmp != NULL)
	{
		if (tmp->argument == NULL && tmp->redirection == NULL)
			return (1);
		tmp = tmp->pipe;
	}
	return (0);
}

void		clear_multi_command(t_command *command)
{
	t_command	*tmp;

	tmp = NULL;
	while (command != NULL)
	{
		tmp = command->pipe;
		ft_lstclear(&command->argument, free);
		ft_lstclear(&command->redirection, dealloc_redirection);
		free(command);
		command = tmp;
	}
}

t_command	*setup_command(void)
{
	t_command	*ret;

	ret = malloc(sizeof(t_command));
	if (ret == NULL)
		return (NULL);
	ret->argument = NULL;
	ret->redirection = NULL;
	ret->pipe = NULL;
	return (ret);
}

int			parser_fail(t_managparse *manag, char **str, t_command *base)
{
	manag->command = base;
	clear_multi_command(manag->command);
	*str = manag->str;
	manag->spipe->last_ret = 2;
	return (1);
}

int			parser(char **str, t_redir *redir, t_pipe *spipe)
{
	t_managparse	manag;
	t_command		*base;

	manag.str = *str;
	manag.spipe = spipe;
	while (*manag.str)
	{
		manag.command = setup_command();
		base = manag.command;
		if (parser_token(&manag))
			return (parser_fail(&manag, str, base));
		if (check_pipe(base))
		{
			error_parser(NULL, ft_strdup("parse error near '|'"));
			return (parser_fail(&manag, str, base));
		}
		manag.command = base;
		execution(manag.command, redir, spipe);
		clear_multi_command(manag.command);
	}
	*str = manag.str;
	return (0);
}
