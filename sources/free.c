/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 13:58:07 by bemoreau          #+#    #+#             */
/*   Updated: 2021/02/25 00:25:11 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		free_struct(t_pipe *spipe, t_parser *parser, t_command *command)
{
	free_spipe(spipe);
	spipe = NULL;
	//if (command)
	//	clear_multi_command(command);
	if (parser)
		free(parser->argument);
	return (-1);
}

int		free_spipe(t_pipe *spipe)
{
	int i;
	i = 0;
	if (spipe->child)
		free(spipe->child);
	if (spipe->pid)
		free(spipe->pid);
	if (spipe->ret)
		free(spipe->ret);
	if (spipe->b_ret)
		free(spipe->b_ret);
	if (spipe->l_env)
	{
		dealloc_tab(spipe->l_env);
		spipe->l_env = NULL;
	}
	return (-1);
}
