/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 13:58:07 by bemoreau          #+#    #+#             */
/*   Updated: 2021/02/23 16:11:32 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_struct(s_pipe *spipe, t_redir *redir, t_command *command)
{
	exit(42);
}

int		free_spipe(s_pipe *spipe)
{
	int i;

	i = 0;
	free(spipe->child);
	free(spipe->pid);
	free(spipe->ret);
	if (spipe->l_env)
	{
		dealloc_tab(spipe->l_env);
		spipe->l_env = NULL;
	}
	return (-1);
}